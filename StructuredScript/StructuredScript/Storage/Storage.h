#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_H
#define STRUCTURED_SCRIPT_STORAGE_H

#include <map>

#include "TempMemory.h"

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

			virtual Ptr *addStorage(const std::string &name) override;

			virtual IStorage *findStorage(const std::string &name, bool localOnly) override;

			virtual IType::Ptr *addType(const std::string &name) override;

			virtual IType::Ptr findType(const std::string &name, bool localOnly) override;

			virtual IMemory::Ptr *addMemory(const std::string &name) override;

			virtual IMemory::Ptr findMemory(const std::string &name, bool localOnly) override;

			virtual IMemory::Ptr *addOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findOperatorMemory(const std::string &name, bool localOnly) override;

			virtual IMemory::Ptr *addTypenameOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findTypenameOperatorMemory(const std::string &name, bool localOnly) override;

			virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

			virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, bool localOnly) override;

			virtual bool remove(const IMemory *target) override;

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