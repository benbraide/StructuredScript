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

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BinaryOperatorNode::clone(){
	return std::make_shared<BinaryOperatorNode>(value_, leftOperand_, rightOperand_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::BinaryOperatorNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (value_ == "::"){
		auto memory = Query::Node::resolveAsObject(rightOperand_, Query::Node::resolveAsStorage(leftOperand_, storage));
		if (memory == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve expression!", expr)));
		}

		return memory->object();
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
