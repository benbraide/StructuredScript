#include "IndexNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IndexNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IndexNode::clone(){
	return std::make_shared<IndexNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::IndexNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->evaluate(storage, exception, expr);
}

std::string StructuredScript::Nodes::IndexNode::str(){
	return ("[" + value_->str() + "]");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IndexNode::value(){
	return value_;
}
