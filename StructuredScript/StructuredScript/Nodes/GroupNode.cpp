#include "GroupNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::GroupNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::GroupNode::clone(){
	return std::make_shared<GroupNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::GroupNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->evaluate(storage, exception, expr);
}

std::string StructuredScript::Nodes::GroupNode::str(){
	return ("(" + value_->str() + ")");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::GroupNode::value(){
	return value_;
}
