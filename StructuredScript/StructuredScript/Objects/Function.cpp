#include "Function.h"

bool StructuredScript::Objects::Function::init(IStorage *storage, IExceptionManager *exception, INode *expr){
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

	return true;
}

bool StructuredScript::Objects::Function::isDefined(){
	return (definition_ != nullptr);
}

bool StructuredScript::Objects::Function::equals(Any::Ptr target){
	auto function = dynamic_cast<Function *>(target->base());
	if (function == nullptr || !type_->isEqual(function->type_) || types_.size() != function->types_.size())
		return false;

	for (auto type = types_.begin(), targetType = function->types_.begin(); type != types_.end() && targetType != function->types_.end(); ++type, ++targetType){
		if (!(*type)->isEqual(*targetType))
			return false;
	}

	return true;
}

bool StructuredScript::Objects::Function::accepts(int count){
	if (count < limits_.first)//Count is less than min requirement
		return false;

	return (limits_.second == -1 || count <= limits_.second);
}

int StructuredScript::Objects::Function::score(const ArgListType &args){
	if (!accepts(static_cast<int>(args.size())))
		return 0;

	if (args.empty())
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

int StructuredScript::Objects::Function::score(const TypeListType &args){
	if (!accepts(static_cast<int>(args.size())))
		return 0;

	if (args.empty())
		return 1;

	auto total = 0;
	unsigned int index = 0;

	for (auto type : args){
		auto score = score_(type, index++);
		if (score < 1)
			return 0;

		total += score;
	}

	return total;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Function::call(const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr){
	IStorage::ExternalCallType call = nullptr;
	if (definition_ == nullptr){
		auto attributes = (memory_ == nullptr) ? nullptr : memory_->attributes();
		if (attributes == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot call an undefined function!", expr)));
		}

		auto callAttribute = attributes->getAttribute("Call");//Check if there's a CallAttribute
		if (callAttribute == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot call an undefined function!", expr)));
		}

		call = storage->findExternalCall(dynamic_cast<IAttributeWithArgument *>(callAttribute.get())->arg()->str());
		if (call == nullptr){//Undefined
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot call an undefined function!", expr)));
		}
	}

	auto param = list_.begin();
	auto arg = args.begin();

	IMemory::Ptr expansionMemory;
	IExpansion *expansion = nullptr;
	Storage::Storage parameterStorage(storage);

	for (; arg != args.end() && param != list_.end(); ++arg, ++param){//Create parameter objects
		if (expansion != nullptr){//Bad expression
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Invalid function parameter list!", expr)));
		}

		auto memory = dynamic_cast<IDeclarationNode *>(param->get())->allocate(&parameterStorage, exception, expr);
		if (Query::ExceptionManager::has(exception))//Failed to allocate memory
			return nullptr;

		auto object = memory->object();
		expansion = (object == nullptr) ? nullptr : dynamic_cast<IExpansion *>(object->base());
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
			if (!Query::Node::isInitialization(*param) && !Query::Node::isExpandedTypeIdentifier(dynamic_cast<IDeclarationNode *>(param->get())->type())){
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + (*param)->str() + "': Missing argument for parameter!", expr)));
			}

			(*param)->evaluate(&parameterStorage, exception, expr);
			if (Query::ExceptionManager::has(exception))//Failed to create object
				return nullptr;
		}
	}
	else if (arg != args.end()){//Expanded memory must have been be created
		if (expansion == nullptr){//Too many arguments
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Too many arguments in function call!", expr)));
		}

		for (; arg != args.end(); ++arg){
			expansion->add()->assign(*arg, storage, exception, expr);
			if (Query::ExceptionManager::has(exception))//Failed to create object
				return nullptr;
		}
	}

	if (call != nullptr)//Forward call
		return call(&parameterStorage, exception, expr);

	if (!Query::Node::isEmpty(definition_))
		definition_->evaluate(&parameterStorage, exception, expr);

	Ptr value;//Return value
	if (Query::ExceptionManager::hasReturn(exception)){
		value = exception->get();
		if (value == nullptr)
			value = PrimitiveFactory::createVoid();
		exception->clear();
	}
	else if (Query::ExceptionManager::hasBreak(exception)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'break' found outside loop!", expr)));
	}
	else if (Query::ExceptionManager::hasContinue(exception)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'continue' found outside loop!", expr)));
	}
	else if (!Query::ExceptionManager::has(exception))
		value = PrimitiveFactory::createVoid();
	else
		return nullptr;

	Storage::Memory converter(nullptr, type_, value, nullptr);//For converting return value
	converter.assign(value, storage, exception, expr);

	return Query::ExceptionManager::has(exception) ? nullptr : converter.object();
}

int StructuredScript::Objects::Function::score_(IType::Ptr type, unsigned int index){
	IType::Ptr target;
	if (index < list_.size()){
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

	return 0;
}
