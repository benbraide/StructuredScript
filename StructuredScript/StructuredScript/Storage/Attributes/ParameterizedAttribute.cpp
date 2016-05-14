#include "ParameterizedAttribute.h"

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::ParameterizedAttribute::ptr(){
	return shared_from_this();
}

bool StructuredScript::Storage::ParameterizedAttribute::appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->appliesTo(memory, storage, exception, expr);
}

void StructuredScript::Storage::ParameterizedAttribute::apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
	value_->apply(memory, storage, exception, expr);
}

void StructuredScript::Storage::ParameterizedAttribute::apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
	value_->apply(node, storage, exception, expr);
}

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::ParameterizedAttribute::spawn(INode::Ptr args, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	return (args == nullptr || Query::Node::isEmpty(args)) ? shared_from_this() : nullptr;
}

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::ParameterizedAttribute::find(const std::string &name, IStorage *storage, 
	IExceptionManager *exception, INode *expr){
	return value_->find(name, storage, exception, expr);
}

StructuredScript::Interfaces::MemoryAttribute::Ptr StructuredScript::Storage::ParameterizedAttribute::value(){
	return value_;
}

StructuredScript::INode::Ptr StructuredScript::Storage::ParameterizedAttribute::arg(){
	return arg_;
}

bool StructuredScript::Storage::ParameterizedAttribute::appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->appliesTo(node, storage, exception, expr);
}
