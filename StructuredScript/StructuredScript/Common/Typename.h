#pragma once

#ifndef STRUCTURED_SCRIPT_TYPENAME_H
#define STRUCTURED_SCRIPT_TYPENAME_H

#include "../Storage/MemoryState.h"
#include "../Storage/MemoryAttributes.h"

#include "../Interfaces/IType.h"

namespace StructuredScript{
	enum Typename{
		TYPE_NAME_ANY,
		TYPE_NAME_VOID,
		TYPE_NAME_BOOLEAN,
		TYPE_NAME_BIT,
		TYPE_NAME_BYTE,
		TYPE_NAME_CHAR,
		TYPE_NAME_UCHAR,
		TYPE_NAME_SHORT,
		TYPE_NAME_USHORT,
		TYPE_NAME_INT,
		TYPE_NAME_UINT,
		TYPE_NAME_LONG,
		TYPE_NAME_ULONG,
		TYPE_NAME_LLONG,
		TYPE_NAME_ULLONG,
		TYPE_NAME_FLOAT,
		TYPE_NAME_DOUBLE,
		TYPE_NAME_LDOUBLE,
		TYPE_NAME_STRING,
		TYPE_NAME_NONE
	};

	class DeclaredType{
	public:
		typedef StructuredScript::Storage::MemoryState		MemoryState;
		typedef StructuredScript::Storage::MemoryAttribute	MemoryAttribute;

		DeclaredType(IType *type, const MemoryState &state, const MemoryAttribute &attribute)
			: type_(type), state_(state), attribute_(attribute){}

		bool operator ==(const DeclaredType &right) const;

		bool operator ==(const IType *right) const;

		bool operator !=(const DeclaredType &right) const;

		bool operator !=(const IType *right) const;

		bool isCompatibleWith(const DeclaredType &target) const;

		bool isCompatibleWith(const IType *target) const;

		bool isEqual(const DeclaredType &target, bool strictly = true) const;

		bool isEqual(const IType *target, bool strictly = true) const;

		MemoryState &getState();

		MemoryAttribute &getAttribute();

	private:
		IType *type_;
		MemoryState state_;
		MemoryAttribute attribute_;
	};
}

#endif /* !STRUCTURED_SCRIPT_TYPENAME_H */