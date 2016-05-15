#pragma once

#ifndef STRUCTURED_SCRIPT_VOID_OBJECT_H
#define STRUCTURED_SCRIPT_VOID_OBJECT_H

#include "Primitive.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		class Void : public Primitive, public IVoid{
		public:
			Void()
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_VOID)){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_VOID_OBJECT_H */