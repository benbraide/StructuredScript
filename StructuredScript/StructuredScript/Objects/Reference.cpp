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

StructuredScript::IAny::Ptr StructuredScript::Objects::Reference::assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->assign(value, right, storage, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Reference::evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->evaluateLeftUnary(value, storage, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Reference::evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->evaluateRightUnary(value, storage, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Reference::evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->object()->evaluateBinary(value, right, storage, exception, expr);
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
