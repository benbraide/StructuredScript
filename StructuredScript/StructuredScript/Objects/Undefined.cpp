#include "Undefined.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Undefined::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;//TODO: Throw exception
}

StructuredScript::IType::Ptr StructuredScript::Objects::Undefined::type(){
	return (memory_ == nullptr) ? nullptr : memory_->type();
}

bool StructuredScript::Objects::Undefined::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

std::string StructuredScript::Objects::Undefined::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "undefined";
}

int StructuredScript::Objects::Undefined::rank(){
	return -1;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Undefined::promote_(Primitive *target){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Undefined::evaluate_(const std::string &value, INumber *right, IExceptionManager *exception, INode *expr){
	return nullptr;//TODO: Throw exception
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Undefined::evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr){
	return nullptr;//TODO: Throw exception
}
