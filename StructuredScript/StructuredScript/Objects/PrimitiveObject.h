#pragma once

#ifndef STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_OBJECT_H
#define STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_OBJECT_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Types/Type.h"
#include "../Common/Factory.h"

#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		class PrimitiveObject : public IStorage{
		public:
			typedef std::map<std::string, MemoryInfo>	MemoryListType;

			PrimitiveObject(IType::Ptr type, IMemory::Ptr &memory)
				: type_(type), memory_(&memory){}

			virtual IStorage *parent() override;

			virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

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

			virtual IAny::Ptr ptr() = 0;

		private:
			IType::Ptr type_;
			IMemory::Ptr *memory_;
			MemoryListType objects_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_OBJECT_H */