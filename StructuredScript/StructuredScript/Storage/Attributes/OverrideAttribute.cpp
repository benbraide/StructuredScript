#include "OverrideAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::OverrideAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::OverrideAttribute::appliesTo(IMemory *memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

bool StructuredScript::Storage::OverrideAttribute::appliesTo(INode *node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::Node::isDeclaration(node);
}
