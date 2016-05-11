#pragma once

#ifndef STRUCTURED_SCRIPT_TEMP_MEMORY_H
#define STRUCTURED_SCRIPT_TEMP_MEMORY_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/INode.h"

namespace StructuredScript{
	namespace Storage{
		class TempMemory : public IMemory{
		public:
			TempMemory(IStorage *storage, IAny::Ptr value)
				: storage_(storage), value_(value){}

			virtual Ptr ptr() override;

			virtual void assign(IAny::Ptr object, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr object() override;

			virtual DeclaredType *type() override;

			virtual IMemoryAttributes *attributes() override;

			virtual IStorage *storage() override;

		private:
			IStorage *storage_;
			IAny::Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_TEMP_MEMORY_H */