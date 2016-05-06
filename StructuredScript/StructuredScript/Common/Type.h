#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_H
#define STRUCTURED_SCRIPT_TYPE_H

#include <map>

#include "Query.h"

namespace StructuredScript{
	class Type : public IType, public IStorage{
	public:
		typedef std::list<Type *>					ParentListType;
		typedef std::map<std::string, IType::Ptr>	TypeListType;
		typedef std::map<std::string, IMemory::Ptr>	MemoryListType;

		Type(IStorage *storage, const std::string &name)
			: storage_(storage), name_(name){}

		virtual Ptr ptr() override;

		virtual IStorage *storage() override;

		virtual bool isEqual(const IType &target) const override;

		virtual bool isParent(const IType &target) const override;

		virtual bool isCompatibleWith(const IType &target) const override;

		virtual Ptr getCompatibleType(const IType &target) override;

		virtual std::string name() const override;

		virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

		virtual IStorage *findStorage(const std::string &name, bool localOnly) override;

		virtual IMemory::Ptr *addMemory(const std::string &name) override;

		virtual IMemory::Ptr findMemory(const std::string &name, bool localOnly) override;

		virtual IType::Ptr findType(const std::string &name, bool localOnly) override;

		virtual bool remove(const IMemory *target) override;

	private:
		std::string name_;
		IStorage *storage_;

		TypeListType types_;
		MemoryListType objects_;
		ParentListType parents_;
	};
}

#endif /* !STRUCTURED_SCRIPT_TYPE_H */