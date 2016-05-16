#pragma once

#ifndef STRUCTURED_SCRIPT_BYTE_OBJECT_H
#define STRUCTURED_SCRIPT_BYTE_OBJECT_H

#include "TypedPrimitive.h"

namespace StructuredScript{
	namespace Objects{
		class Byte : public TypedPrimitive<unsigned char, -1>, public IByte {
		public:
			explicit Byte(unsigned char value)
				: TypedPrimitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_BYTE), value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr getIndexValue(unsigned int index) override;

		protected:
			virtual IAny::Ptr evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_BYTE_OBJECT_H */