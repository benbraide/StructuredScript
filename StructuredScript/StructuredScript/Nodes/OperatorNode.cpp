#include "OperatorNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::UnaryOperatorNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::UnaryOperatorNode::clone(){
	return std::make_shared<UnaryOperatorNode>(left_, value_, operand_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::UnaryOperatorNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto value = operand_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (left_ && value_ == "!")
		return PrimitiveFactory::createBool(!value->truth(storage, exception, expr));

	if (left_ && value_ == "::"){
		auto memory = Query::Node::resolveAsObject(operand_, storage);
		if (memory == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve expression!", expr)));
		}

		return memory->object();
	}

	auto primitive = dynamic_cast<IPrimitiveObject *>(value->base());
	if (primitive != nullptr)
		return left_ ? primitive->evaluateLeftUnary(value_, exception, expr) : primitive->evaluateRightUnary(value_, exception, expr);

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value_ + "': Operand mismatch!", expr)));
}

std::string StructuredScript::Nodes::UnaryOperatorNode::str(){
	return (value_ + operand_->str());
}

std::string StructuredScript::Nodes::UnaryOperatorNode::value() const{
	return value_;
}

std::shared_ptr<StructuredScript::Interfaces::Node> StructuredScript::Nodes::UnaryOperatorNode::operand(){
	return operand_;
}

StructuredScript::IStorage *StructuredScript::Nodes::UnaryOperatorNode::resolveStorage(IStorage *storage){
	return (left_ && value_ == "::") ? Query::Node::resolveAsStorage(operand_, dynamic_cast<IStorage *>(IGlobalStorage::globalStorage)) : nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Nodes::UnaryOperatorNode::resolveType(IStorage *storage){
	return (left_ && value_ == "::") ? Query::Node::resolveAsType(operand_, dynamic_cast<IStorage *>(IGlobalStorage::globalStorage)) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::UnaryOperatorNode::resolveMemory(IStorage *storage){
	return (left_ && value_ == "::") ? Query::Node::resolveAsObject(operand_, dynamic_cast<IStorage *>(IGlobalStorage::globalStorage)) : nullptr;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::clone(){
	return std::make_shared<BinaryOperatorNode>(value_, leftOperand_, rightOperand_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::BinaryOperatorNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (value_ == "::" || value_ == "()"){//Scope | Call
		auto memory = (value_[0] == ':') ? resolveMemory(storage) : Query::Node::resolveAsObject(leftOperand_, storage);
		if (memory == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve expression!", expr)));
		}

		if (value_[0] == ':')//Scope
			return memory->object();

		auto functionMemory = dynamic_cast<IFunctionMemory *>(memory.get());
		if (functionMemory != nullptr){//Call function
			IFunction::ArgListType args;

			functionMemory->resolveArgs(rightOperand_, args, storage, exception, expr);
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			auto match = functionMemory->find(args);//Find matching function
			if (match == nullptr){
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + str() + "': No function found taking the specified arguments!", expr)));
			}

			auto function = dynamic_cast<IFunction *>(match->object()->base());
			if (function == nullptr){
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + str() + "': Target is not a function!", expr)));
			}

			auto targetStorage = dynamic_cast<IMemory *>(functionMemory)->storage();
			if (targetStorage == nullptr)//Function is not a member -- use definition storage
				targetStorage = match->storage();

			return function->call(args, targetStorage, exception, expr);
		}
	}

	auto leftValue = leftOperand_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (value_ == "||" && leftValue->truth(storage, exception, expr))//Short-circuit evaluation
		return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createBool(true);

	if (value_ == "&&" && !leftValue->truth(storage, exception, expr))//Short-circuit evaluation
		return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createBool(false);

	if (value_ == "."){//Member access -- don't evaluate right operand
		return nullptr;
	}

	auto rightValue = rightOperand_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	std::string value;
	if (value_ == "===" || value_ == "!=="){//Compare types first
		auto leftType = leftValue->type(), rightType = rightValue->type();
		if (leftType == nullptr || rightType == nullptr || !leftType->isEqual(rightType))
			return PrimitiveFactory::createBool(value_[0] == '!');

		value = value_.substr(0, 2);
	}
	else
		value = value_;

	auto primitive = dynamic_cast<IPrimitiveObject *>(leftValue->base());
	if (primitive != nullptr)
		return primitive->evaluateBinary(value, rightValue, storage, exception, expr);

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value_ + "': Operand mismatch!", expr)));
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

std::string StructuredScript::Nodes::BinaryOperatorNode::value() const{
	return value_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::leftOperand(){
	return leftOperand_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::rightOperand(){
	return rightOperand_;
}

StructuredScript::IStorage *StructuredScript::Nodes::BinaryOperatorNode::resolveStorage(IStorage *storage){
	if (value_ == "::"){
		storage = Query::Node::resolveAsStorage(leftOperand_, storage);
		return (storage == nullptr) ? nullptr : Query::Node::resolveAsStorage(rightOperand_, storage);
	}

	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Nodes::BinaryOperatorNode::resolveType(IStorage *storage){
	if (value_ == "::"){
		storage = Query::Node::resolveAsStorage(leftOperand_, storage);
		return (storage == nullptr) ? nullptr : Query::Node::resolveAsType(rightOperand_, storage);
	}

	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::BinaryOperatorNode::resolveMemory(IStorage *storage){
	if (value_ == "."){//Member access
		auto memory = Query::Node::resolveAsObject(leftOperand_, storage);
		auto object = (memory == nullptr) ? nullptr : memory->object();
		
		auto storageObject = dynamic_cast<IStorage *>(object.get());
		if (storageObject == nullptr)
			return nullptr;

		memory = Query::Node::resolveAsObject(rightOperand_, storageObject);
		auto functionMemory = dynamic_cast<IFunctionMemory *>(memory.get());
		if (functionMemory != nullptr)//Set object as storage
			functionMemory->setStorage(storageObject);

		return memory;
	}

	if (value_ == "::"){
		storage = Query::Node::resolveAsStorage(leftOperand_, storage);
		return (storage == nullptr) ? nullptr : Query::Node::resolveAsObject(rightOperand_, storage);
	}

	return nullptr;
}
