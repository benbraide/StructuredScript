#pragma once

#ifndef STRUCTURED_SCRIPT_STRING_OBJECT_H
#define STRUCTURED_SCRIPT_STRING_OBJECT_H

#include "Real.h"

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Types/Type.h"
#include "../Common/Factory.h"

#include "../Interfaces/Storages/IGlobalStorage.h"
#include "../Scanner/Scanner.h"
#include "../Scanner/Wells/StringCharacterWell.h"
#include "../Parser/Parser.h"

namespace StructuredScript{
	namespace Objects{
		class String : public TypedPrimitive<std::string, Primitive::STRING_RANK>, public IStorage, public IString{
		public:
			String(const std::string &value);

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

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

			static void init(std::shared_ptr<Type> type, IScanner &scanner, IParser &parser);

		protected:
			virtual IAny::Ptr promote_(Primitive *target) override;

			virtual IAny::Ptr evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr) override;

			IMemory::Ptr length_;
			static INode::Ptr lengthNode_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STRING_OBJECT_H */