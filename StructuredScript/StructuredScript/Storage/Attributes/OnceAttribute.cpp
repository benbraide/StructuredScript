#include "OnceAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::OnceAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::OnceAttribute::appliesTo(IMemory *memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

bool StructuredScript::Storage::OnceAttribute::appliesTo(INode *node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::Node::isDeclaration(node);
}
