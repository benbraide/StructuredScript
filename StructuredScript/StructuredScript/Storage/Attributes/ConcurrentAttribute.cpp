#include "ConcurrentAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::ConcurentAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::ConcurentAttribute::appliesTo(IMemory *memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

bool StructuredScript::Storage::ConcurentAttribute::appliesTo(INode *node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (Query::Node::isControl(node) || Query::Node::isPlainBlock(node));
}