#include "LockedAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::LockedAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::LockedAttribute::appliesTo(IMemory *memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::LockedAttribute::appliesTo(INode *node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::Node::isDeclaration(node);
}
