#include "TypeObject.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<TypeObject>(value_);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::IAny *StructuredScript::Objects::TypeObject::base(){
	return this;
}

StructuredScript::IType::Ptr StructuredScript::Objects::TypeObject::type(){
	return type_;
}

void StructuredScript::Objects::TypeObject::setMemory(IMemory *memory){
	memory_ = memory;
}

StructuredScript::IMemory *StructuredScript::Objects::TypeObject::memory(){
	return memory_;
}

bool StructuredScript::Objects::TypeObject::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

std::string StructuredScript::Objects::TypeObject::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "";
}

StructuredScript::IType::Ptr StructuredScript::Objects::TypeObject::value(){
	return value_;
}
