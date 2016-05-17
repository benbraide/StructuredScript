#pragma once

#ifndef STRUCTURED_SCRIPT_EXPANSION_OBJECT_H
#define STRUCTURED_SCRIPT_EXPANSION_OBJECT_H

#include <vector>

#include "Primitive.h"
#include "../Storage/Memory.h"

#include "../Interfaces/Storages/IGlobalStorage.h"
#include "../Scanner/Scanner.h"
#include "../Scanner/Wells/StringCharacterWell.h"
#include "../Parser/Parser.h"

namespace StructuredScript{
	namespace Objects{
		class Expansion : public Primitive, public IStorage, public IExpansion{
		public:
			typedef std::vector<IMemory::Ptr> MemoryListType;

			Expansion(IType::Ptr type);

			virtual Ptr assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IStorage *parent() override;

			virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

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

			virtual void expand(IFunction::ArgListType &args) override;

			virtual IMemory::Ptr add() override;

			static void init();

		private:
			IMemory::Ptr length_;
			MemoryListType entries_;

			static INode::Ptr lengthNode_;
			static ExternalCallType lengthCallback_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_EXPANSION_OBJECT_H */