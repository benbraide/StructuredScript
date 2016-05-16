#include "Reference.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Reference::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Reference::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->clone(storage, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Reference::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->cast(type, storage, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Reference::base(){
	return value_->object()->base();
}

StructuredScript::IType::Ptr StructuredScript::Objects::Reference::type(){
	return value_->object()->type();
}

void StructuredScript::Objects::Reference::setMemory(IMemory *memory){
	memory_ = memory;
}

StructuredScript::IMemory *StructuredScript::Objects::Reference::memory(){
	return memory_;
}

bool StructuredScript::Objects::Reference::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->truth(storage, exception, expr);
}

std::string StructuredScript::Objects::Reference::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->str(storage, exception, expr);
}
