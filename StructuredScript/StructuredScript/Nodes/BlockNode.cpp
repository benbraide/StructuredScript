#include "BlockNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BlockNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BlockNode::clone(){
	return std::make_shared<BlockNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::BlockNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->evaluate(storage, exception, expr);
}

std::string StructuredScript::Nodes::BlockNode::str(){
	return ("{" + value_->str() + "}");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BlockNode::value(){
	return value_;
}
