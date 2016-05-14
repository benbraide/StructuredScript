#include "Factory.h"

#include "../Objects/Undefined.h"
#include "../Objects/Void.h"
#include "../Objects/NaN.h"
#include "../Objects/Bool.h"
#include "../Objects/Bit.h"
#include "../Objects/Byte.h"
#include "../Objects/Integer.h"
#include "../Objects/Real.h"
#include "../Objects/TypeObject.h"
#include "../Objects/IndexObject.h"

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createUndefined(){
	return std::make_shared<Objects::Undefined>();
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createVoid(){
	return std::make_shared<Objects::Void>();
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createNaN(){
	return std::make_shared<Objects::NaN>();
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createBool(bool value){
	return std::make_shared<Objects::Bool>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createBit(bool value){
	return std::make_shared<Objects::Bit>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createByte(unsigned char value){
	return std::make_shared<Objects::Byte>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createChar(char value){
	return std::make_shared<Objects::Char>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createUChar(unsigned char value){
	return std::make_shared<Objects::UChar>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createShort(short value){
	return std::make_shared<Objects::Short>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createUShort(unsigned short value){
	return std::make_shared<Objects::UShort>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createInt(int value){
	return std::make_shared<Objects::Int>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createUInt(unsigned int value){
	return std::make_shared<Objects::UInt>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createLong(long value){
	return std::make_shared<Objects::Long>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createULong(unsigned long value){
	return std::make_shared<Objects::ULong>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createLLong(long long value){
	return std::make_shared<Objects::LLong>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createULLong(unsigned long long value){
	return std::make_shared<Objects::ULLong>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createFloat(float value){
	return std::make_shared<Objects::Float>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createDouble(double value){
	return std::make_shared<Objects::Double>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createLDouble(long double value){
	return std::make_shared<Objects::LDouble>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createString(const std::string &value){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createTypeObject(IType::Ptr value){
	return std::make_shared<Objects::TypeObject>(value);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::createIndexObject(IType::Ptr type, unsigned int value, IMemory *target){
	return std::make_shared<Objects::IndexObject>(type, value, target);
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::create(int rank){
	switch (rank){
	case Objects::Primitive::CHAR_RANK:
		return createChar('\0');
	case Objects::Primitive::UCHAR_RANK:
		return createUChar('\0');
	case Objects::Primitive::SHORT_RANK:
		return createShort(0);
	case Objects::Primitive::USHORT_RANK:
		return createUShort(0);
	case Objects::Primitive::INT_RANK:
		return createInt(0);
	case Objects::Primitive::UINT_RANK:
		return createUInt(0);
	case Objects::Primitive::LONG_RANK:
		return createLong(0);
	case Objects::Primitive::ULONG_RANK:
		return createULong(0);
	case Objects::Primitive::LLONG_RANK:
		return createLLong(0);
	case Objects::Primitive::ULLONG_RANK:
		return createULLong(0);
	case Objects::Primitive::FLOAT_RANK:
		return createFloat(0);
	case Objects::Primitive::DOUBLE_RANK:
		return createDouble(0);
	case Objects::Primitive::LDOUBLE_RANK:
		return createLDouble(0);
	case Objects::Primitive::STRING_RANK:
		return createString("");
	default:
		break;
	}

	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::PrimitiveFactory::create(Typename type){
	switch (type){
	case Typename::TYPE_NAME_NAN:
		return createNaN();
	case Typename::TYPE_NAME_BOOLEAN:
		return createBool(false);
	case Typename::TYPE_NAME_BIT:
		return createBit(false);
	case Typename::TYPE_NAME_BYTE:
		return createByte('\0');
	case Typename::TYPE_NAME_CHAR:
		return createChar('\0');
	case Typename::TYPE_NAME_UCHAR:
		return createUChar('\0');
	case Typename::TYPE_NAME_SHORT:
		return createShort(0);
	case Typename::TYPE_NAME_USHORT:
		return createUShort(0);
	case Typename::TYPE_NAME_INT:
		return createInt(0);
	case Typename::TYPE_NAME_UINT:
		return createUInt(0);
	case Typename::TYPE_NAME_LONG:
		return createLong(0);
	case Typename::TYPE_NAME_ULONG:
		return createULong(0);
	case Typename::TYPE_NAME_LLONG:
		return createLLong(0);
	case Typename::TYPE_NAME_ULLONG:
		return createULLong(0);
	case Typename::TYPE_NAME_FLOAT:
		return createFloat(0);
	case Typename::TYPE_NAME_DOUBLE:
		return createDouble(0);
	case Typename::TYPE_NAME_LDOUBLE:
		return createLDouble(0);
	case Typename::TYPE_NAME_STRING:
		return createString("");
	default:
		break;
	}

	return nullptr;
}
