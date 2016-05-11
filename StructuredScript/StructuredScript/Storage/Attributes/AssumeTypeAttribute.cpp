#include "AssumeTypeAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::AssumeTypeAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::AssumeTypeAttribute::appliesTo(IMemory *memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::AssumeTypeAttribute::appliesTo(INode *node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (Query::Node::isAssignment(node) || Query::Node::isParameter(node) || Query::Node::isMember(node));
}
