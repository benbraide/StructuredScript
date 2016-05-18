#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_H
#define STRUCTURED_SCRIPT_MEMORY_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/TypeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/INode.h"
#include "../Interfaces/Storages/IMemoryBackdoor.h"

#include "MemoryState.h"

namespace StructuredScript{
	namespace Storage{
		class Memory : public IMemory, public IMemoryBackdoor{
		public:
			Memory(IStorage *storage, IType::Ptr type, IAny::Ptr value, IMemoryAttributes::Ptr attributes, bool assignMemory = true);

			virtual Ptr ptr() override;

			virtual void assign(IAny::Ptr object, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr object() override;

			virtual IType::Ptr type() override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual IStorage *storage() override;

			virtual void assign(IAny::Ptr object) override;

		private:
			IStorage *storage_;
			IType::Ptr type_;
			IAny::Ptr value_;
			IMemoryAttributes::Ptr attributes_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_H */