#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_H
#define STRUCTURED_SCRIPT_MEMORY_H

#include "TempMemory.h"
#include "MemoryAttributes.h"

namespace StructuredScript{
	namespace Storage{
		class Memory : public TempMemory{
		public:
			Memory(IStorage *storage, IAny::Ptr value, IType::Ptr type, const MemoryState &state, const MemoryAttributes &attributes)
				: TempMemory(storage, value), type_(type, state), attributes_(attributes){}

			virtual DeclaredType *type() override;

			virtual IMemoryAttributes *attributes() override;

		private:
			DeclaredType type_;
			MemoryAttributes attributes_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_H */