#pragma once

#ifndef STRUCTURED_SCRIPT_BOOL_OBJECT_H
#define STRUCTURED_SCRIPT_BOOL_OBJECT_H

#include "TypedPrimitive.h"

namespace StructuredScript{
	namespace Objects{
		class Bool : public TypedPrimitive<bool, -1>, public IBool {
		public:
			explicit Bool(bool value)
				: TypedPrimitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_BOOLEAN), value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_BOOL_OBJECT_H */