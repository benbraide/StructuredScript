#include "Primitive.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	return type->isEqual(*type_) ? ptr() : nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Primitive::type(){
	return type_;
}

void StructuredScript::Objects::Primitive::setMemory(IMemory *memory){
	memory_ = memory;
}

StructuredScript::IMemory *StructuredScript::Objects::Primitive::memory(){
	return memory_;
}

bool StructuredScript::Objects::Primitive::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

std::string StructuredScript::Objects::Primitive::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "";
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	return nullptr;//TODO: Throw exception
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	return nullptr;//TODO: Throw exception
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateBinary(const std::string &value, Ptr right, IExceptionManager *exception, INode *expr){
	auto primitive = dynamic_cast<Primitive *>(right.get());//TODO: Get base object
	if (primitive == nullptr)
		return nullptr;//TODO: Throw exception

	if (primitive->rank() < rank())
		return evaluate_(value, false, promote_(primitive), exception, expr);

	if (primitive->rank() > rank())
		return primitive->evaluate_(value, true, primitive->promote_(this), exception, expr);

	return evaluate_(value, false, right, exception, expr);
}
