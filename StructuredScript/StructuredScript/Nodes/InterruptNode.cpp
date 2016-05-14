#include "InterruptNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ReturnNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ReturnNode::clone(){
	return std::make_shared<ReturnNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ReturnNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (exception == nullptr)
		return PrimitiveFactory::createUndefined();

	auto value = Query::Node::isEmpty(value_) ? nullptr : value_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	exception->setReturn(value);
	return nullptr;
}

std::string StructuredScript::Nodes::ReturnNode::str(){
	return Query::Node::isEmpty(value_) ? "return" : ("return " + value_->str());
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::InterruptCommon::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BreakNode::clone(){
	return std::make_shared<BreakNode>();
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::BreakNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (exception == nullptr)
		return PrimitiveFactory::createUndefined();

	exception->setBreak();
	return nullptr;
}

std::string StructuredScript::Nodes::BreakNode::str(){
	return "break";
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ContinueNode::clone(){
	return std::make_shared<ContinueNode>();
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ContinueNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (exception == nullptr)
		return PrimitiveFactory::createUndefined();

	exception->setContinue();
	return nullptr;
}

std::string StructuredScript::Nodes::ContinueNode::str(){
	return "continue";
}
