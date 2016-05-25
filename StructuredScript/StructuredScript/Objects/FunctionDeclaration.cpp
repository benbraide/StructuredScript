#include "FunctionDeclaration.h"

bool StructuredScript::Objects::FunctionDeclaration::init(bool isRightUnary, IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::Node::split(",", parameters_, list_);

	if (!list_.empty()){
		limits_.first = limits_.second = static_cast<int>(list_.size());

		auto progress = 0;
		for (auto param = list_.rbegin(); param != list_.rend(); ++param){//Extract parameters info
			auto declaration = dynamic_cast<IDeclarationNode *>(param->get());
			if (declaration == nullptr){
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + (*param)->str() + "': Expected declaration as parameter!", expr)));

				return false;
			}

			auto type = declaration->type();
			if (Query::Node::isExpandedTypeIdentifier(type)){//Expanded type
				if (progress != 0){
					Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
						Query::ExceptionManager::combine("'" + parameters_->str() + "': Bad parameter list!", expr)));

					return false;
				}

				--limits_.first;//Decrease minimum required
				limits_.second = -1;//Infinite max

				progress = 1;
			}
			else if (Query::Node::isInitialization(*param)){//Initialization declaration
				if (progress > 1){
					Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
						Query::ExceptionManager::combine("'" + parameters_->str() + "': Bad parameter list!", expr)));

					return false;
				}

				--limits_.first;//Decrease minimum required
				progress = 1;
			}
			else if (progress < 2)
				progress = 2;

			auto resolvedType = Query::Node::resolveAsType(type, storage);
			if (resolvedType == nullptr){
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + type->str() + "': could not resolve type!", expr)));

				return false;
			}

			types_.push_front(resolvedType);
		}
	}
	else//Empty parameter list
		limits_ = { 0, 0 };

	rightUnary_ = isRightUnary;

	auto declType = dynamic_cast<IDeclaredType *>(type_.get());
	if (declType != nullptr){//Check for static declaration
		if (Storage::MemoryState(declType->states()).isStatic())
			return true;//Non-member function
	}

	auto storageType = dynamic_cast<IType *>(storage);
	if (storageType != nullptr)//Member function
		owner_ = storageType->ptr();

	return true;
}

bool StructuredScript::Objects::FunctionDeclaration::isDefined() const{
	return false;
}

bool StructuredScript::Objects::FunctionDeclaration::isStatic() const{
	return isStatic_;
}

bool StructuredScript::Objects::FunctionDeclaration::isMember() const{
	return (owner_ != nullptr);
}

bool StructuredScript::Objects::FunctionDeclaration::equals(Any::Ptr target){
	auto targetBase = target->base();
	auto function = dynamic_cast<FunctionDeclaration *>(targetBase.get());
	if (function == nullptr || types_.size() != function->types_.size())
		return false;

	for (auto type = types_.begin(), targetType = function->types_.begin(); type != types_.end() && targetType != function->types_.end(); ++type, ++targetType){
		if ((*type)->isAny() != (*targetType)->isAny() || !(*type)->isEqual(*targetType))
			return false;
	}

	return true;
}

bool StructuredScript::Objects::FunctionDeclaration::accepts(int count){
	if (count < limits_.first)//Count is less than min requirement
		return false;

	return (limits_.second == -1 || count <= limits_.second);
}

int StructuredScript::Objects::FunctionDeclaration::score(bool rightUnary, IAny::Ptr object, const ArgListType &args){
	if (!accepts(static_cast<int>(args.size())))
		return 0;

	if (rightUnary_ != rightUnary)
		return -2;

	if (owner_ != nullptr){//Compare object types
		auto type = (object == nullptr) ? nullptr : getObjectType_(object);
		if (type == nullptr || (!owner_->isEqual(type) && !type->isParent(owner_)))//Exact | Parent type expected
			return -1;
	}

	auto arg = args.begin();
	if (arg == args.end())
		return 1;

	if (args.empty())//Matched
		return 1;

	auto total = 0;
	unsigned int index = 0;

	for (auto arg : args){
		auto type = arg->type();
		if (type == nullptr)//Type expected
			return 0;

		auto score = score_(type, index++);
		if (score < 1)
			return 0;

		total += score;
	}

	return total;
}

StructuredScript::IType::Ptr StructuredScript::Objects::FunctionDeclaration::declaredType(){
	return type_;
}

int StructuredScript::Objects::FunctionDeclaration::score(bool rightUnary, IAny::Ptr object, const TypeListType &args){
	if (!accepts(static_cast<int>(args.size())))
		return 0;

	if (rightUnary_ != rightUnary)
		return -2;

	if (owner_ != nullptr){//Compare object types
		auto type = (object == nullptr) ? nullptr : getObjectType_(object);
		if (type == nullptr || !owner_->isEqual(type))//Exact type expected
			return -1;
	}

	if (args.empty())//Matched
		return 1;

	auto total = 0;
	unsigned int index = 0;

	for (auto arg : args){
		auto score = score_(arg, index++);
		if (score < 1)
			return 0;

		total += score;
	}

	return total;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::FunctionDeclaration::prep_(const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr){
	auto param = list_.begin();
	auto arg = args.begin();

	IMemory::Ptr expansionMemory;
	IExpansion *expansion = nullptr;

	for (; arg != args.end() && param != list_.end(); ++arg, ++param){//Create parameter objects
		if (expansion != nullptr){//Bad expression
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Invalid function parameter list!", expr)));

			return nullptr;
		}

		auto memory = dynamic_cast<IDeclarationNode *>(param->get())->allocate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))//Failed to allocate memory
			return nullptr;

		expansion = dynamic_cast<IExpansion *>(memory->object().get());
		if (expansion != nullptr){//Add entry
			expansionMemory = memory;//Store memory reference for when memory is temporary
			memory = expansion->add();
		}

		memory->assign(*arg, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))//Failed to create object
			return nullptr;
	}

	if (param != list_.end()){//Parameters must be initialization declarations
		for (; param != list_.end(); ++param){
			auto declaration = dynamic_cast<IDeclarationNode *>(param->get());
			if (Query::Node::isExpandedTypeIdentifier(declaration->type())){//Expansion -- allocate
				auto memory = declaration->allocate(storage, exception, expr);
				if (Query::ExceptionManager::has(exception))//Failed to create object
					return nullptr;

				expansion = dynamic_cast<IExpansion *>(memory->object().get());
				if (expansion == nullptr){//Insert undefined
					auto backdoor = dynamic_cast<IMemoryBackdoor *>(memory.get());
					if (backdoor == nullptr){
						Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
							Query::ExceptionManager::combine("Error during function call!", expr)));

						return nullptr;
					}

					backdoor->assign(PrimitiveFactory::createUndefined());
				}
				else//Expansion object created
					expansionMemory = memory;//Store memory reference for when memory is temporary
			}
			else if (Query::Node::isInitialization(*param)){//Initialization -- evaluate
				auto memory = (*param)->evaluate(storage, exception, expr);
				if (Query::ExceptionManager::has(exception))//Failed to create object
					return nullptr;
			}
			else{//Too few arguments
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + (*param)->str() + "': Missing argument for parameter!", expr)));

				return nullptr;
			}
		}
	}
	else if (arg != args.end()){//Expanded memory must have been be created
		if (expansion == nullptr){//Too many arguments
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Too many arguments in function call!", expr)));

			return nullptr;
		}

		for (; arg != args.end(); ++arg){
			expansion->add()->assign(*arg, storage, exception, expr);
			if (Query::ExceptionManager::has(exception))//Failed to create object
				return nullptr;
		}
	}

	return expansionMemory;
}

int StructuredScript::Objects::FunctionDeclaration::score_(IType::Ptr type, unsigned int index){
	IType::Ptr target;
	if (index < types_.size()){
		target = *std::next(types_.begin(), index);

		auto stackedType = dynamic_cast<IStackedType *>(target.get());
		if (stackedType != nullptr)
			target = stackedType->value();
	}
	else{//Assume last parameter has expanded type
		auto stackedType = dynamic_cast<IStackedType *>(types_.rbegin()->get());
		if (stackedType == nullptr)
			return 0;

		target = stackedType->value();
	}

	if (target->isEqual(type))
		return 3;

	if (type->isParent(target))
		return 2;

	if (target->isCompatibleWith(type))
		return 1;

	auto typeStorage = dynamic_cast<IStorage *>(type.get());
	if (typeStorage != nullptr && typeStorage->findTypenameOperatorMemory(target->base(), IStorage::SEARCH_LOCAL) != nullptr)
		return 1;

	return 0;
}

StructuredScript::IType::Ptr StructuredScript::Objects::FunctionDeclaration::getObjectType_(IAny::Ptr object){
	auto property = dynamic_cast<IProperty *>(object.get());
	return (property == nullptr) ? object->type() : property->propertyType();
}
