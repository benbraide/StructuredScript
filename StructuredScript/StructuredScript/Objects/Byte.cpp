#include "Byte.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Byte::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<Byte>(value_);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Byte::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (type->isEqual(*type_))
		return ptr();

	auto primitive = dynamic_cast<IPrimitiveType *>(type.get());
	if (primitive == nullptr)
		return nullptr;

	switch (primitive->value()){
	case Typename::TYPE_NAME_CHAR:
		return PrimitiveFactory::createChar(static_cast<char>(value_));
	case Typename::TYPE_NAME_UCHAR:
		return PrimitiveFactory::createUChar(value_);
	case Typename::TYPE_NAME_SHORT:
		return PrimitiveFactory::createShort(static_cast<short>(value_));
	case Typename::TYPE_NAME_USHORT:
		return PrimitiveFactory::createUShort(static_cast<unsigned short>(value_));
	case Typename::TYPE_NAME_INT:
		return PrimitiveFactory::createInt(static_cast<int>(value_));
	case Typename::TYPE_NAME_UINT:
		return PrimitiveFactory::createUInt(static_cast<unsigned int>(value_));
	case Typename::TYPE_NAME_LONG:
		return PrimitiveFactory::createLong(static_cast<long>(value_));
	case Typename::TYPE_NAME_ULONG:
		return PrimitiveFactory::createULong(static_cast<unsigned long>(value_));
	case Typename::TYPE_NAME_LLONG:
		return PrimitiveFactory::createLLong(static_cast<long long>(value_));
	case Typename::TYPE_NAME_ULLONG:
		return PrimitiveFactory::createULLong(static_cast<unsigned long long>(value_));
	default:
		break;
	}

	return nullptr;
}

bool StructuredScript::Objects::Byte::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return (value_ != static_cast<unsigned char>('\0'));
}

std::string StructuredScript::Objects::Byte::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	std::string value;
	for (unsigned char i = static_cast<unsigned char>(0); i < static_cast<unsigned char>(8); ++i)
		value = std::to_string((value_ >> i) & static_cast<unsigned char>(1)) + value;

	return ("0b" + value);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Byte::evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	if (value == "~")
		return std::make_shared<Byte>(~value_);

	return TypedPrimitive::evaluateLeftUnary(value, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Byte::evaluateBinary(const std::string &value, Ptr right, IExceptionManager *exception, INode *expr){
	if (value != "[]")
		return Primitive::evaluateBinary(value, right, exception, expr);

	if (dynamic_cast<IInteger *>(right->base()) == nullptr)
		return nullptr;//TODO: Throw exception

	auto index = static_cast<unsigned char>(getIndex(right));
	if (memory_ == nullptr)
		return PrimitiveFactory::createBit(((value_ >> (static_cast<unsigned char>(7) - index)) & static_cast<unsigned char>(1)) != static_cast<unsigned char>(0));

	return PrimitiveFactory::createIndexObject(type_, index, memory_);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Byte::getIndexValue(unsigned int index){
	return PrimitiveFactory::createBit(((value_ >> (static_cast<unsigned char>(7) - static_cast<unsigned char>(index))) &
		static_cast<unsigned char>(1)) != static_cast<unsigned char>(0));
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Byte::evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr){
	if (value == "|")
		return std::make_shared<Byte>(left->value() | right->value());

	if (value == "^")
		return std::make_shared<Byte>(left->value() ^ right->value());

	if (value == "&")
		return std::make_shared<Byte>(left->value() & right->value());

	return TypedPrimitive::evaluate_(value, left, right, exception, expr);
}
