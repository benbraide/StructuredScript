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

bool StructuredScript::Objects::Function::accepts(int count){
	if (count < limits_.first)//Count is less than min requirement
		return false;

	return (limits_.second == -1 || count <= limits_.second);
}

int StructuredScript::Objects::Function::score(const ArgListType &args){
	if (!accepts(static_cast<int>(args.size())))
		return 0;

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
	return nullptr;
}

int StructuredScript::Objects::Function::score_(IType::Ptr type, unsigned int index){
	IType::Ptr target;
	if (index < list_.size())
		target = *std::next(types_.begin(), index);
	else//Assume last parameter has expanded type
		target = dynamic_cast<IStackedType *>(types_.rbegin()->get())->value();

	if (target->isEqual(type))
		return 3;

	if (type->isParent(target))
		return 2;

	if (target->isCompatibleWith(type))
		return 1;

	return 0;
}
