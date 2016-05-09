#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_OBJECT_H
#define STRUCTURED_SCRIPT_TYPE_OBJECT_H

#include "../Common/Query.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		class TypeObject : public IAny, public ITypeObject{
		public:
			explicit TypeObject(IType::Ptr value)
				: type_(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_TYPE)), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny *base() override;

			virtual IType::Ptr type() override;

			virtual void setMemory(IMemory *memory) override;

			virtual IMemory *memory() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IType::Ptr value() override;

		protected:
			IType::Ptr type_;
			IType::Ptr value_;
			IMemory *memory_ = nullptr;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_TYPE_OBJECT_H */