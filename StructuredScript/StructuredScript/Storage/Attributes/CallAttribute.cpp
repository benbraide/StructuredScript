#include "CallAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::CallAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::CallAttribute::appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::CallAttribute::appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::Node::isFunction(node);
}

void StructuredScript::Storage::CallAttribute::apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){}

void StructuredScript::Storage::CallAttribute::apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){}

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::CallAttribute::spawn(INode::Ptr args, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (args == nullptr || Query::Node::isEmpty(args)) ? shared_from_this() : nullptr;
}

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::CallAttribute::find(const std::string &name, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::INode::Ptr StructuredScript::Storage::CallAttribute::arg(){
	return arg_;
}
