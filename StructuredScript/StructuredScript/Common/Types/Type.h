#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_H
#define STRUCTURED_SCRIPT_TYPE_H

#include <map>
#include <list>

#include "../TypeQuery.h"
#include "../../Interfaces/IMemory.h"
#include "../../Storage/MemoryState.h"
#include "../../Interfaces/Storages/IFunctionMemory.h"

namespace StructuredScript{
	class Type : public IType, public IStorage{
	public:
		typedef std::list<Ptr>									ParentListType;
		typedef std::map<std::string, IType::Ptr>				TypeListType;
		typedef std::map<std::string, IMemory::Ptr>				MemoryListType;
		typedef std::map<std::string, IMemoryAttribute::Ptr>	MemoryAttributeListType;

		Type(IStorage *storage, const std::string &name)
			: storage_(storage), name_(name){}

		virtual Ptr ptr() override;

		virtual Ptr base() override;

		virtual IStorage *storage() override;

		virtual bool isAny() override;

		virtual bool isEqual(Ptr target) override;

		virtual bool isParent(Ptr target) override;

		virtual bool isCompatibleWith(Ptr target, bool family = false) override;

		virtual Ptr getCompatibleType(Ptr target, bool family = false) override;

		virtual std::string name() const override;

		virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

		virtual IStorage *findStorage(const std::string &name, bool localOnly) override;

		virtual std::shared_ptr<IType> *addType(const std::string &name) override;

		virtual IType::Ptr findType(const std::string &name, bool localOnly) override;

		virtual IMemory::Ptr *addMemory(const std::string &name) override;

		virtual IMemory::Ptr findMemory(const std::string &name, bool localOnly) override;

		virtual IMemory::Ptr *addOperatorMemory(const std::string &name) override;

		virtual IMemory::Ptr findOperatorMemory(const std::string &name, bool localOnly) override;

		virtual IMemory::Ptr *addTypenameOperatorMemory(const std::string &name) override;

		virtual IMemory::Ptr findTypenameOperatorMemory(const std::string &name, bool localOnly) override;

		virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

		virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, bool localOnly) override;

		virtual bool remove(IMemory::Ptr target) override;

	private:
		std::string name_;
		IStorage *storage_;

		TypeListType types_;
		MemoryListType objects_;
		MemoryAttributeListType attributes_;
		ParentListType parents_;
	};
}

#endif /* !STRUCTURED_SCRIPT_TYPE_H */