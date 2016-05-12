#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_MEMORY_H
#define STRUCTURED_SCRIPT_FUNCTION_MEMORY_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/INode.h"
#include "../Interfaces/Storages/IFunctionMemory.h"

#include "MemoryAttributes.h"

namespace StructuredScript{
	namespace Storage{
		class FunctionMemory : public IMemory, public IFunctionMemory{
		public:
			FunctionMemory(IStorage *storage, IType::Ptr type, const MemoryState &state, const MemoryAttributes &attributes)
				: storage_(storage), type_(type, state), attributes_(attributes){}

			virtual Ptr ptr() override;

			virtual void assign(IAny::Ptr object, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr object() override;

			virtual DeclaredType *type() override;

			virtual IMemoryAttributes *attributes() override;

			virtual IStorage *storage() override;

		private:
			IStorage *storage_;
			DeclaredType type_;
			MemoryAttributes attributes_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_MEMORY_H */