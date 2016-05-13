#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_OBJECT_H
#define STRUCTURED_SCRIPT_FUNCTION_OBJECT_H

#include "Primitive.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		class FunctionObject : public Primitive, public ITypeObject{
		public:
			explicit FunctionObject(IType::Ptr value)
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_TYPE)), value_(value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny *base() override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IType::Ptr value() override;

		protected:
			IType::Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_OBJECT_H */