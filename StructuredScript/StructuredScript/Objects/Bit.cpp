#include "Bit.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Bit::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<Bit>(value_);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Bit::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (type->isEqual(*type_))
		return ptr();

	auto primitive = dynamic_cast<IPrimitiveType *>(type.get());
	if (primitive == nullptr)
		return nullptr;

	switch (primitive->value()){
	case Typename::TYPE_NAME_BOOLEAN:
		return PrimitiveFactory::createBool(value_);
	default:
		break;
	}

	return nullptr;
}

bool StructuredScript::Objects::Bit::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_;
}

std::string StructuredScript::Objects::Bit::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_ ? "bit::one" : "bit::zero";
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Bit::evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	if (value == "~")
		return std::make_shared<Bit>(!value_);

	return TypedPrimitive::evaluateLeftUnary(value, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Bit::evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr){
	if (value == "|")
		return std::make_shared<Bit>(left->value() || right->value());

	if (value == "^")
		return std::make_shared<Bit>(left->value() != right->value());

	if (value == "&")
		return std::make_shared<Bit>(left->value() && right->value());

	return TypedPrimitive::evaluate_(value, left, right, exception, expr);
}
