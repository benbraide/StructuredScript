#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_H
#define STRUCTURED_SCRIPT_STORAGE_H

#include <map>

#include "FunctionMemory.h"
#include "../Interfaces/Storages/IPureStorage.h"

namespace StructuredScript{
	namespace Storage{
		class Storage : public IStorage, public IPureStorage{
		public:
			typedef std::shared_ptr<IStorage>						Ptr;
			typedef std::map<std::string, IType::Ptr>				TypeListType;
			typedef std::map<std::string, IMemoryAttribute::Ptr>	MemoryAttributeListType;
			typedef std::map<std::string, Ptr>						StorageListType;

			typedef std::map<std::string, MemoryInfo>				MemoryListType;
			typedef std::map<std::string, MemoryInfo>				OperatorMemoryListType;
			typedef std::map<IType::Ptr, MemoryInfo>				TypenameOperatorMemoryListType;

			typedef std::map<std::string, IMemory::Ptr>				UsedMemoryListType;
			typedef std::map<std::string, IMemory::Ptr>				UsedOperatorMemoryListType;
			typedef std::map<IType::Ptr, IMemory::Ptr>				UsedTypenameOperatorMemoryListType;

			typedef std::map<std::string, IType::Ptr>				UsedTypeListType;
			typedef std::list<IStorage *>							UsedStorageListType;

			Storage(IStorage *parent)
				: parent_(parent){}

			virtual IStorage *parent() override;

			virtual Ptr *addStorage(const std::string &name) override;

			virtual IStorage *findStorage(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IType::Ptr *addType(const std::string &name) override;

			virtual IType::Ptr findType(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual MemoryInfo *addMemory(const std::string &name) override;

			virtual IMemory::Ptr findMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr findFunctionMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual MemoryInfo *addOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual MemoryInfo *addTypenameOperatorMemory(IType::Ptr name) override;

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

		protected:
			TypenameOperatorMemoryListType::iterator findTypeOperator_(IType::Ptr name);

			UsedTypenameOperatorMemoryListType::iterator findUsedTypeOperator_(IType::Ptr name);

			IStorage *parent_;
			TypeListType types_;
			MemoryAttributeListType attributes_;
			StorageListType storages_;

			MemoryListType objects_;
			OperatorMemoryListType operators_;
			TypenameOperatorMemoryListType typeOperators_;

			UsedMemoryListType usedObjects_;
			UsedOperatorMemoryListType usedOperators_;
			UsedTypenameOperatorMemoryListType usedTypeOperators_;

			UsedTypeListType usedTypes_;
			UsedStorageListType usedStorages_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_H */