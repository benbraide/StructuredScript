#pragma once

#ifndef STRUCTURED_SCRIPT_PROPERTY_OBJECT_H
#define STRUCTURED_SCRIPT_PROPERTY_OBJECT_H

#include "Any.h"
#include "../Common/ExceptionManager.h"
#include "../Interfaces/Storages/IFunctionMemory.h"
#include "../Nodes/OperatorNode.h"

namespace StructuredScript{
	namespace Objects{
		class Property : public Any{
		public:
			typedef std::shared_ptr<IFunctionMemory> FunctionMemoryType;

			explicit Property(IType::Ptr type);

			virtual ~Property(){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr base() override;

			virtual Ptr assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IType::Ptr type() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool remove(IMemory::Ptr target) override;

		protected:
			void getMemory_(const std::string &name, IStorage *storage, FunctionMemoryType &target);

			FunctionMemoryType get_;
			FunctionMemoryType set_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PROPERTY_OBJECT_H */