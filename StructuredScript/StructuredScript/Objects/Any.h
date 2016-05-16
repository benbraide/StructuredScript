#pragma once

#ifndef STRUCTURED_SCRIPT_ANY_OBJECT_H
#define STRUCTURED_SCRIPT_ANY_OBJECT_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/Types/ICompoundType.h"

namespace StructuredScript{
	namespace Objects{
		class Any : public IAny, public IStorage{
		public:
			explicit Any(IType::Ptr type)
				: type_(type){}

			virtual ~Any(){}

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr base() override;

			virtual Ptr assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IType::Ptr type() override;

			virtual void setMemory(IMemory *memory) override;

			virtual IMemory *memory() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

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

		protected:
			IType::Ptr type_;
			IMemory *memory_ = nullptr;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ANY_OBJECT_H */