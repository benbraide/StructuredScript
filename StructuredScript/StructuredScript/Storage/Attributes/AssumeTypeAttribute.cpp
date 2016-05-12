#include "AssumeTypeAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::AssumeTypeAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::AssumeTypeAttribute::appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::AssumeTypeAttribute::appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (Query::Node::isInitialization(node) || Query::Node::isParameter(node) || Query::Node::isMember(node));
}
