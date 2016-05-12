#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARED_TYPE_H
#define STRUCTURED_SCRIPT_DECLARED_TYPE_H

#include "../Storage/MemoryState.h"
#include "../Interfaces/IType.h"

namespace StructuredScript{
	class DeclaredType{
	public:
		typedef StructuredScript::Storage::MemoryState MemoryState;

		DeclaredType(IType::Ptr type, const MemoryState &state)
			: type_(type), state_(state){}

		bool operator ==(const DeclaredType &right) const;

		bool operator ==(const IType::Ptr right) const;

		bool operator !=(const DeclaredType &right) const;

		bool operator !=(const IType::Ptr right) const;

		bool isCompatibleWith(const DeclaredType &target, bool family = false) const;

		bool isCompatibleWith(const IType::Ptr target, const MemoryState &state, bool family = false) const;

		bool isEqual(const DeclaredType &target, bool strictly = true) const;

		bool isEqual(const IType::Ptr target, bool strictly = true) const;

		IType::Ptr type();

		MemoryState &state();

	private:
		IType::Ptr type_;
		MemoryState state_;
	};
}

#endif /* !STRUCTURED_SCRIPT_DECLARED_TYPE_H */