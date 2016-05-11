#include "AssumeConstnessAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::AssumeConstnessAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::AssumeConstnessAttribute::appliesTo(IMemory *memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (memory != nullptr);
}

bool StructuredScript::Storage::AssumeConstnessAttribute::appliesTo(INode *node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return (Query::Node::isAssignment(node) || Query::Node::isParameter(node) || Query::Node::isMember(node));
}
