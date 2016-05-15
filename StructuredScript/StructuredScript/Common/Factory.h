#pragma once

#ifndef STRUCTURED_SCRIPT_FACTORY_H
#define STRUCTURED_SCRIPT_FACTORY_H

#include "Typename.h"

#include "../Interfaces/IAny.h"
#include "../Interfaces/IMemory.h"

namespace StructuredScript{
	class PrimitiveFactory{
	public:
		static IAny::Ptr createUndefined();

		static IAny::Ptr createVoid();

		static IAny::Ptr createNaN();

		static IAny::Ptr createReference(IMemory::Ptr value);

		static IAny::Ptr createBool(bool value);

		static IAny::Ptr createBit(bool value);

		static IAny::Ptr createByte(unsigned char value);

		static IAny::Ptr createChar(char value);

		static IAny::Ptr createUChar(unsigned char value);

		static IAny::Ptr createLChar(char &value);

		static IAny::Ptr createShort(short value);

		static IAny::Ptr createUShort(unsigned short value);

		static IAny::Ptr createInt(int value);

		static IAny::Ptr createUInt(unsigned int value);

		static IAny::Ptr createLong(long value);

		static IAny::Ptr createULong(unsigned long value);

		static IAny::Ptr createLLong(long long value);

		static IAny::Ptr createULLong(unsigned long long value);

		static IAny::Ptr createFloat(float value);

		static IAny::Ptr createDouble(double value);

		static IAny::Ptr createLDouble(long double value);

		static IAny::Ptr createString(const std::string &value);

		static IAny::Ptr createTypeObject(IType::Ptr value);

		static IAny::Ptr createIndexObject(IType::Ptr type, unsigned int value, IMemory *target);

		static IAny::Ptr create(int rank);

		static IAny::Ptr create(Typename type);
	};
}

#endif /* !STRUCTURED_SCRIPT_FACTORY_H */