#include "EmptyNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::EmptyNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::EmptyNode::clone(){
	return std::make_shared<EmptyNode>();
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::EmptyNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot evaluate an empty node!", expr)));
}

std::string StructuredScript::Nodes::EmptyNode::str(){
	return "";
}

void StructuredScript::Nodes::EmptyNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::EmptyNode::attributes(){
	return nullptr;
}
