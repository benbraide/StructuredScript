#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARED_TYPE_H
#define STRUCTURED_SCRIPT_DECLARED_TYPE_H

#include "../Storage/MemoryState.h"
#include "../Interfaces/IType.h"

namespace StructuredScript{
	class DeclaredType{
	public:
		typedef StructuredScript::Storage::MemoryState MemoryState;

		DeclaredType(IType *type, const MemoryState &state)
			: type_(type), state_(state){}

		bool operator ==(const DeclaredType &right) const;

		bool operator ==(const IType *right) const;

		bool operator !=(const DeclaredType &right) const;

		bool operator !=(const IType *right) const;

		bool isCompatibleWith(const DeclaredType &target, bool family = false) const;

		bool isCompatibleWith(const IType *target, const MemoryState &state, bool family = false) const;

		bool isEqual(const DeclaredType &target, bool strictly = true) const;

		bool isEqual(const IType *target, bool strictly = true) const;

		IType *type();

		MemoryState &state();

	private:
		IType *type_;
		MemoryState state_;
	};
}

#endif /* !STRUCTURED_SCRIPT_DECLARED_TYPE_H */