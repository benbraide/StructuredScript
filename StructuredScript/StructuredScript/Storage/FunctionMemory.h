#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_MEMORY_H
#define STRUCTURED_SCRIPT_FUNCTION_MEMORY_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "Memory.h"

#include "../Interfaces/Storages/IGlobalStorage.h"
#include "../Interfaces/Storages/IFunctionMemory.h"

namespace StructuredScript{
	namespace Storage{
		class FunctionMemory : public IMemory, public IFunctionMemory{
		public:
			typedef std::list<Ptr> ListType;

			FunctionMemory(IStorage *storage)
				: storage_(storage){}

			FunctionMemory(const ListType &components);

			virtual Ptr ptr() override;

			virtual void assign(IAny::Ptr object, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr object() override;

			virtual IType::Ptr type() override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual IStorage *storage() override;

			virtual void setStorage(IStorage *storage) override;

			virtual Ptr add(IAny::Ptr function, IMemoryAttributes::Ptr attributes) override;

			virtual Ptr find(const IFunction::ArgListType &args) override;

			virtual Ptr find(const IFunction::TypeListType &args) override;

			virtual void resolveArgs(INode::Ptr args, IFunction::ArgListType &resolved, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			unsigned int count() const;

			void getStaticMemories(ListType &list);

		private:
			ListType::iterator find_(IAny::Ptr function);

			IStorage *storage_;
			ListType list_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_MEMORY_H */