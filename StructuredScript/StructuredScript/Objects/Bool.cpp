#include "Bool.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Bool::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<Bool>(value_);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Bool::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (type->isEqual(*type_))
		return ptr();

	auto primitive = dynamic_cast<IPrimitiveType *>(type.get());
	if (primitive == nullptr)
		return nullptr;

	switch (primitive->value()){
	case Typename::TYPE_NAME_BIT:
		return PrimitiveFactory::createBit(value_);
	default:
		break;
	}

	return nullptr;
}

bool StructuredScript::Objects::Bool::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_;
}

std::string StructuredScript::Objects::Bool::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_ ? "true" : "false";
}
