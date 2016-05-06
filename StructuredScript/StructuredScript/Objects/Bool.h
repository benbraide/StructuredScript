#pragma once

#ifndef STRUCTURED_SCRIPT_BOOL_OBJECT_H
#define STRUCTURED_SCRIPT_BOOL_OBJECT_H

#include "TypedPrimitive.h"

namespace StructuredScript{
	namespace Objects{
		class Bool : public TypedPrimitive<bool, -1>, public IBool {
		public:
			Bool(bool value)
				: TypedPrimitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_BOOLEAN), value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::make_shared<Bool>(value_);
			}

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override{
				if (type->isEqual(*type_))
					return ptr();

				auto primitive = dynamic_cast<IPrimitiveType *>(type.get());
				if (primitive == nullptr)
					return nullptr;

				switch (primitive->value()){
				case Typename::TYPE_NAME_BIT:
					return nullptr;
				default:
					break;
				}

				return nullptr;
			}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return value_ ? "true" : "false";
			}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_BOOL_OBJECT_H */