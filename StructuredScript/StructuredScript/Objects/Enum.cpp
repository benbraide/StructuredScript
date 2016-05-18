#include "Enum.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Enum::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return shared_from_this();
}

std::string StructuredScript::Objects::Enum::name() const {
	return (type_->name() + "::" + name_);
}
