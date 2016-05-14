#include "ConcurrentAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::ConcurentAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::ConcurentAttribute::appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::ConcurentAttribute::appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (Query::Node::isFunction(node) || Query::Node::isControl(node) || Query::Node::isPlainBlock(node));
}

void StructuredScript::Storage::ConcurentAttribute::apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){}

void StructuredScript::Storage::ConcurentAttribute::apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::ConcurentAttribute::spawn(INode::Ptr args, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (args == nullptr || Query::Node::isEmpty(args)) ? shared_from_this() : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::ConcurentAttribute::find(const std::string &name, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}
