#pragma once

#ifndef STRUCTURED_SCRIPT_SPECIALIZED_STORAGE_H
#define STRUCTURED_SCRIPT_SPECIALIZED_STORAGE_H

#include "Storage.h"

namespace StructuredScript{
	namespace Storage{
		class SharedStorage : public IStorage, public IPureStorage{
		public:
			typedef std::shared_ptr<IStorage> Ptr;

			SharedStorage(IStorage &first, IStorage &then)
				: first_(&first), then_(&then){}

			virtual IStorage *parent() override;

			virtual Ptr *addStorage(const std::string &name) override;

			virtual IStorage *findStorage(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IType::Ptr *addType(const std::string &name) override;

			virtual IType::Ptr findType(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addMemory(const std::string &name) override;

			virtual IMemory::Ptr findMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr findFunctionMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addTypenameOperatorMemory(IType::Ptr name) override;

			virtual IMemory::Ptr findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

			virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual ExternalCallType findExternalCall(const std::string &name) override;

			virtual bool remove(IMemory::Ptr target) override;

			virtual bool use(IStorage *storage) override;

			virtual bool use(const std::string &name, IType::Ptr value) override;

			virtual bool use(const std::string &name, IMemory::Ptr value) override;

			virtual bool useOperator(const std::string &name, Memory::Ptr value) override;

			virtual bool useTypenameOperator(IType::Ptr name, IMemory::Ptr value) override;

		private:
			IStorage *first_;
			IStorage *then_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_SPECIALIZED_STORAGE_H */