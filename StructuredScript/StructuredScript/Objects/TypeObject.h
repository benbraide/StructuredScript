#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_OBJECT_H
#define STRUCTURED_SCRIPT_TYPE_OBJECT_H

#include "Primitive.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		class TypeObject : public Primitive, public ITypeObject{
		public:
			explicit TypeObject(IType::Ptr value)
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_TYPE)), value_(value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IType::Ptr value() override;

		protected:
			virtual Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override;

			IType::Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_TYPE_OBJECT_H */