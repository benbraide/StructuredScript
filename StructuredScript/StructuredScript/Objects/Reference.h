#pragma once

#ifndef STRUCTURED_SCRIPT_REFERENCE_OBJECT_H
#define STRUCTURED_SCRIPT_REFERENCE_OBJECT_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/Types/ICompoundType.h"

namespace StructuredScript{
	namespace Objects{
		class Reference : public IAny{
		public:
			explicit Reference(IMemory::Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny *base() override;

			virtual IType::Ptr type() override;

			virtual void setMemory(IMemory *memory) override;

			virtual IMemory *memory() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

		protected:
			IMemory::Ptr value_;
			IMemory *memory_ = nullptr;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_REFERENCE_OBJECT_H */