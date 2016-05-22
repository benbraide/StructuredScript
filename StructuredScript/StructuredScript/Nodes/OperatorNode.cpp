#include "OperatorNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::UnaryOperatorNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::UnaryOperatorNode::clone(){
	return std::make_shared<UnaryOperatorNode>(left_, value_, operand_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::UnaryOperatorNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (left_ && value_ == "::"){
		auto memory = resolveMemory(storage);
		if (memory == nullptr){//Try type
			auto type = resolveType(storage);
			if (type != nullptr)
				return PrimitiveFactory::createTypeObject(type);

			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve expression!", expr)));
		}

		if (dynamic_cast<IFunctionMemory *>(memory.get()) == nullptr)
			return memory->object();

		return PrimitiveFactory::createFunctionObject(memory);
	}

	if (!left_ && value_ == "()"){//Call
		auto resolver = dynamic_cast<IMemoryResolver *>(operand_.get());
		auto memory = (resolver == nullptr) ? nullptr : resolver->resolveMemory(storage);
		if (memory != nullptr){
			auto functionMemory = dynamic_cast<IFunctionMemory *>(memory.get());
			if (functionMemory != nullptr)//Call function
				return functionMemory->call(false, {}, exception, expr);

			return call_(memory->object(), exception, expr);
		}

		auto value = operand_->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return call_(value, exception, expr);
	}

	auto value = operand_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (value_ == ";")
		return PrimitiveFactory::createUndefined();

	if (left_ && value_ == "!")
		return PrimitiveFactory::createBool(!value->truth(storage, exception, expr));

	if (!left_ && value_ == "..."){
		if (!Query::Object::isExpansion(value)){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Expected an expansion object!", expr)));
		}

		return PrimitiveFactory::createExpanded(value);
	}

	return left_ ? value->evaluateLeftUnary(value_, storage, exception, expr) : value->evaluateRightUnary(value_, storage, exception, expr);
}

std::string StructuredScript::Nodes::UnaryOperatorNode::str(){
	return left_ ? (value_ + operand_->str()) : (operand_->str() + value_);
}

void StructuredScript::Nodes::UnaryOperatorNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::UnaryOperatorNode::attributes(){
	return nullptr;
}

std::string StructuredScript::Nodes::UnaryOperatorNode::value() const{
	return value_;
}

std::shared_ptr<StructuredScript::Interfaces::Node> StructuredScript::Nodes::UnaryOperatorNode::operand(){
	return operand_;
}

bool StructuredScript::Nodes::UnaryOperatorNode::isLeft() const{
	return left_;
}

StructuredScript::IStorage *StructuredScript::Nodes::UnaryOperatorNode::resolveStorage(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	if (value_ == "::"){
		auto resolver = dynamic_cast<IStorageResolver *>(operand_.get());
		if (resolver == nullptr)
			return nullptr;

		return resolver->resolveStorage(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), IStorage::SEARCH_LOCAL);
	}

	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Nodes::UnaryOperatorNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	if (value_ == "::"){
		auto resolver = dynamic_cast<ITypeResolver *>(operand_.get());
		if (resolver == nullptr)
			return nullptr;

		return resolver->resolveType(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), IStorage::SEARCH_LOCAL);
	}

	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::UnaryOperatorNode::resolveMemory(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	if (value_ == "::"){
		auto resolver = dynamic_cast<IMemoryResolver *>(operand_.get());
		if (resolver == nullptr)
			return nullptr;

		return resolver->resolveMemory(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), IStorage::SEARCH_LOCAL);
	}

	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::UnaryOperatorNode::call_(IAny::Ptr object, IExceptionManager *exception, INode *expr){
	object = object->base();

	auto storage = dynamic_cast<IStorage *>(object.get());
	if (storage == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Object is not callable!", expr)));
	}

	auto function = storage->findOperatorMemory("()");
	auto functionMemory = dynamic_cast<IFunctionMemory *>(function.get());
	if (functionMemory == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Object is not callable!", expr)));
	}

	return functionMemory->call(false, {}, exception, expr);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::clone(){
	return std::make_shared<BinaryOperatorNode>(value_, leftOperand_, rightOperand_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::BinaryOperatorNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (value_ == "::" || value_ == "()"){//Scope | Call
		IMemory::Ptr memory;
		if (value_[0] == '('){
			auto resolver = dynamic_cast<IMemoryResolver *>(leftOperand_.get());
			if (resolver != nullptr)
				memory = resolver->resolveMemory(storage);
		}
		else//Resolve both operands as memory
			memory = resolveMemory(storage);

		if (value_[0] == ':'){//Scope
			if (memory == nullptr){//Try type
				auto type = resolveType(storage);
				if (type != nullptr)
					return PrimitiveFactory::createTypeObject(type);

				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + str() + "': Could not resolve expression!", expr)));
			}

			if (dynamic_cast<IFunctionMemory *>(memory.get()) == nullptr)
				return memory->object();

			return PrimitiveFactory::createFunctionObject(memory);
		}

		if (memory != nullptr){
			auto functionMemory = dynamic_cast<IFunctionMemory *>(memory.get());
			if (functionMemory != nullptr){//Call function
				IFunction::ArgListType args;

				functionMemory->resolveArgs(rightOperand_, args, storage, exception, expr);
				if (Query::ExceptionManager::has(exception))
					return nullptr;

				return functionMemory->call(false, args, exception, expr);
			}

			return call_(memory->object(), storage, exception, expr);
		}

		auto leftValue = leftOperand_->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		auto typeObject = dynamic_cast<ITypeObject *>(leftValue.get());
		if (typeObject == nullptr)
			return call_(leftValue, storage, exception, expr);

		auto rightValue = rightOperand_->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		auto castValue = rightValue->cast(typeObject->value(), storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (castValue == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not perform cast!", expr)));
		}

		return castValue;
	}

	auto leftValue = leftOperand_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (value_ == "||" && leftValue->truth(storage, exception, expr))//Short-circuit evaluation
		return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createBool(true);

	if (value_ == "&&" && !leftValue->truth(storage, exception, expr))//Short-circuit evaluation
		return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createBool(false);

	if (value_ == ";"){
		rightOperand_->evaluate(storage, exception, expr);
		return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createUndefined();
	}

	auto leftValueBase = leftValue->base();
	if (value_ == "."){//Member access -- don't evaluate right operand
		auto objectStorage = dynamic_cast<IStorage *>(leftValueBase.get());
		if (objectStorage == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve expression!", expr)));
		}

		auto resolver = dynamic_cast<IMemoryResolver *>(rightOperand_.get());
		auto memory = (resolver == nullptr) ? nullptr : resolver->resolveMemory(objectStorage, IStorage::SEARCH_FAMILY);
		if (memory == nullptr){//Try type
			auto type = resolveType(storage);
			if (type != nullptr)
				return PrimitiveFactory::createTypeObject(type);

			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve expression!", expr)));
		}

		if (dynamic_cast<IFunctionMemory *>(memory.get()) == nullptr)
			return memory->object();

		return PrimitiveFactory::createFunctionObject(memory);
	}

	auto rightValue = rightOperand_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (value_ == "=" || value_ == "+=" || value_ == "-=" || value_ == "*=" || value_ == "/=" || value_ == "%=" || value_ == "&=" ||
		value_ == "^=" || value_ == "|=" || value_ == "<<=" || value_ == ">>="){//Assignment
		return leftValue->assign(value_, rightValue, storage, exception, expr);
	}

	std::string value;
	if (value_ == "===" || value_ == "!=="){//Compare types first
		auto leftType = leftValue->type(), rightType = rightValue->type();
		if (leftType == nullptr || rightType == nullptr || !leftType->isEqual(rightType))
			return PrimitiveFactory::createBool(value_[0] == '!');

		value = value_.substr(0, 2);
	}
	else
		value = value_;

	return leftValue->evaluateBinary(value, rightValue, storage, exception, expr);
}

std::string StructuredScript::Nodes::BinaryOperatorNode::str(){
	if (value_ == "()" || value_ == "[]" || value_ == "{}")
		return (leftOperand_->str() + value_[0] + rightOperand_->str() + value_[1]);

	if (value_ == ";")
		return (leftOperand_->str() + ";\n" + rightOperand_->str());

	if (value_ == ",")
		return (leftOperand_->str() + value_ + " " + rightOperand_->str());

	if (value_ == "." || value_ == "::")
		return (leftOperand_->str() + value_ + rightOperand_->str());

	return (leftOperand_->str() + " " + value_ + " " + rightOperand_->str());
}

void StructuredScript::Nodes::BinaryOperatorNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::BinaryOperatorNode::attributes(){
	return nullptr;
}

std::string StructuredScript::Nodes::BinaryOperatorNode::value() const{
	return value_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::leftOperand(){
	return leftOperand_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::rightOperand(){
	return rightOperand_;
}

StructuredScript::IStorage *StructuredScript::Nodes::BinaryOperatorNode::resolveStorage(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	if (storage == nullptr)
		return nullptr;

	if (value_ == "::"){
		auto leftResolver = dynamic_cast<IStorageResolver *>(leftOperand_.get());
		auto rightResolver = dynamic_cast<IStorageResolver *>(rightOperand_.get());
		if (leftResolver == nullptr || rightResolver == nullptr)
			return nullptr;

		storage = leftResolver->resolveStorage(storage, searchScope);
		return (storage == nullptr) ? nullptr : rightResolver->resolveStorage(storage, IStorage::SEARCH_LOCAL);
	}

	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Nodes::BinaryOperatorNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	if (storage == nullptr)
		return nullptr;

	if (value_ == "::"){
		auto leftResolver = dynamic_cast<IStorageResolver *>(leftOperand_.get());
		auto rightResolver = dynamic_cast<ITypeResolver *>(rightOperand_.get());
		if (leftResolver == nullptr || rightResolver == nullptr)
			return nullptr;

		storage = leftResolver->resolveStorage(storage, searchScope);
		return (storage == nullptr) ? nullptr : rightResolver->resolveType(storage, IStorage::SEARCH_LOCAL);
	}

	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::BinaryOperatorNode::resolveMemory(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	if (storage == nullptr)
		return nullptr;

	if (value_ == "."){//Member access -- family search
		auto leftResolver = dynamic_cast<IMemoryResolver *>(leftOperand_.get());
		auto rightResolver = dynamic_cast<IMemoryResolver *>(rightOperand_.get());
		if (leftResolver == nullptr || rightResolver == nullptr)
			return nullptr;

		auto memory = leftResolver->resolveMemory(storage, searchScope);
		auto object = (memory == nullptr) ? nullptr : memory->object()->base();
		
		auto storageObject = dynamic_cast<IStorage *>(object.get());
		if (storageObject == nullptr)
			return nullptr;

		return rightResolver->resolveMemory(storageObject, IStorage::SEARCH_FAMILY);
	}

	if (value_ == "::"){//Local search
		auto leftResolver = dynamic_cast<IStorageResolver *>(leftOperand_.get());
		auto rightResolver = dynamic_cast<IMemoryResolver *>(rightOperand_.get());
		if (leftResolver == nullptr || rightResolver == nullptr)
			return nullptr;

		storage = leftResolver->resolveStorage(storage, searchScope);
		return (storage == nullptr) ? nullptr : rightResolver->resolveMemory(storage, IStorage::SEARCH_LOCAL);
	}

	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::BinaryOperatorNode::call_(IAny::Ptr object, IStorage *storage, IExceptionManager *exception, INode *expr){
	object = object->base();

	auto objectStorage = dynamic_cast<IStorage *>(object.get());
	if (objectStorage == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Object is not callable!", expr)));
	}

	auto function = objectStorage->findOperatorMemory("()");
	auto functionMemory = dynamic_cast<IFunctionMemory *>(function.get());
	if (functionMemory == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Object is not callable!", expr)));
	}

	IFunction::ArgListType args;

	functionMemory->resolveArgs(rightOperand_, args, storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return functionMemory->call(false, args, exception, expr);
}
