#include "Undefined.h"

StructuredScript::IType::Ptr StructuredScript::Objects::Undefined::type(){
	return (memory_ == nullptr) ? nullptr : memory_->type();
}

bool StructuredScript::Objects::Undefined::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

std::string StructuredScript::Objects::Undefined::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "undefined";
}
