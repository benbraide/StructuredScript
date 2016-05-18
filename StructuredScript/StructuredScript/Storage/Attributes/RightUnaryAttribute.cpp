#include "RightUnaryAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::RightUnaryAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::RightUnaryAttribute::appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::RightUnaryAttribute::appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (Query::Node::isOperatorIdentifier(node) || Query::Node::isFunction(node));
}

void StructuredScript::Storage::RightUnaryAttribute::apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){}

void StructuredScript::Storage::RightUnaryAttribute::apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::RightUnaryAttribute::spawn(INode::Ptr args, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (args == nullptr || Query::Node::isEmpty(args)) ? shared_from_this() : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::RightUnaryAttribute::find(const std::string &name, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}
