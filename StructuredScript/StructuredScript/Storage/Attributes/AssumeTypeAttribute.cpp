#include "AssumeTypeAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::AssumeTypeAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::AssumeTypeAttribute::appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::AssumeTypeAttribute::appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (Query::Node::isDeclaration(node) || Query::Node::isFunction(node));
}

void StructuredScript::Storage::AssumeTypeAttribute::apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){}

void StructuredScript::Storage::AssumeTypeAttribute::apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::AssumeTypeAttribute::spawn(INode::Ptr args, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (args == nullptr || Query::Node::isEmpty(args)) ? shared_from_this() : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::AssumeTypeAttribute::find(const std::string &name, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}
