#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_H
#define STRUCTURED_SCRIPT_STORAGE_H

#include <map>

#include "FunctionMemory.h"

namespace StructuredScript{
	namespace Storage{
		class Storage : public IStorage{
		public:
			typedef std::shared_ptr<IStorage>						Ptr;
			typedef std::map<std::string, IType::Ptr>				TypeListType;
			typedef std::map<std::string, IMemory::Ptr>				MemoryListType;
			typedef std::map<std::string, IMemoryAttribute::Ptr>	MemoryAttributeListType;
			typedef std::map<std::string, Ptr>						StorageListType;

			Storage(IStorage *parent)
				: parent_(parent){}

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

			virtual IMemory::Ptr *addTypenameOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findTypenameOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

			virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual ExternalCallType findExternalCall(const std::string &name) override;

			virtual bool remove(IMemory::Ptr target) override;

		protected:
			IStorage *parent_;
			TypeListType types_;
			MemoryListType objects_;
			MemoryAttributeListType attributes_;
			StorageListType storages_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_H */