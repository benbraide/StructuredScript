#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARED_TYPE_H
#define STRUCTURED_SCRIPT_DECLARED_TYPE_H

#include "../Storage/MemoryState.h"
#include "../Storage/MemoryAttributes.h"

#include "../Interfaces/IType.h"

namespace StructuredScript{
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

		bool isCompatibleWith(const DeclaredType &target, bool family = false) const;

		bool isCompatibleWith(const IType *target, const MemoryState &state, bool family = false) const;

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

#endif /* !STRUCTURED_SCRIPT_DECLARED_TYPE_H */