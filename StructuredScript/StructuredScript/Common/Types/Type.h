#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_H
#define STRUCTURED_SCRIPT_TYPE_H

#include <map>
#include <list>

#include "../TypeQuery.h"
#include "../../Storage/MemoryState.h"
#include "../../Storage/FunctionMemory.h"
#include "../../Interfaces/Storages/INamespace.h"

namespace StructuredScript{
	class Type : public IType, public IStorage{
	public:
		typedef std::list<Ptr>									ParentListType;
		typedef std::map<std::string, IType::Ptr>				TypeListType;
		typedef std::map<std::string, IMemoryAttribute::Ptr>	MemoryAttributeListType;
		typedef std::map<std::string, ExternalCallType>			ExternalCallListType;

		typedef std::map<std::string, IMemory::Ptr>				MemoryListType;
		typedef std::map<std::string, IMemory::Ptr>				OperatorMemoryListType;
		typedef std::map<IType::Ptr, IMemory::Ptr>				TypenameOperatorMemoryListType;

		typedef StructuredScript::Storage::FunctionMemory::ListType ListType;

		Type(IStorage *storage, const std::string &name)
			: name_(name), storage_(storage){}

		Type(IStorage *storage, const ParentListType &parents, const std::string &name)
			: name_(name), storage_(storage), parents_(parents){}

		virtual Ptr ptr() override;

		virtual Ptr base() override;

		virtual IStorage *storage() override;

		virtual bool isAny() override;

		virtual bool isEqual(Ptr target) override;

		virtual bool isParent(Ptr target) override;

		virtual bool isCompatibleWith(Ptr target, bool family = false) override;

		virtual Ptr getCompatibleType(Ptr target, bool family = false) override;

		virtual std::string name() const override;

		virtual unsigned short states() const override;

		virtual IStorage *parent() override;

		virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

		virtual IStorage *findStorage(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

		virtual std::shared_ptr<IType> *addType(const std::string &name) override;

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

		void addExternalCall(const std::string &name, ExternalCallType value);

	protected:
		TypenameOperatorMemoryListType::iterator findTypeOperator_(IType::Ptr name);

		void extendList_(ListType &list, const std::string &name, unsigned short searchScope);

		void extendOperatorList_(ListType &list, const std::string &name, unsigned short searchScope);

		void extendTypeOperatorList_(ListType &list, IType::Ptr name, unsigned short searchScope);

		std::string name_;
		IStorage *storage_;
		ParentListType parents_;

		TypeListType types_;
		MemoryAttributeListType attributes_;
		ExternalCallListType externalCalls_;

		MemoryListType objects_;
		OperatorMemoryListType operators_;
		TypenameOperatorMemoryListType typeOperators_;
	};
}

#endif /* !STRUCTURED_SCRIPT_TYPE_H */