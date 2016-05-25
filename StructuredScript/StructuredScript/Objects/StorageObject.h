#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_OBJECT_H
#define STRUCTURED_SCRIPT_STORAGE_OBJECT_H

#include "Primitive.h"
#include "PrimitiveObject.h"

#include "../Common/ExceptionManager.h"

namespace StructuredScript{
	namespace Objects{
		class StorageObject : public Primitive, public PrimitiveObject, public IStorageObject{
		public:
			explicit StorageObject(IStorage *value);

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IStorage *value() override;

			static void init();

		protected:
			virtual Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override;

			IStorage *value_;

			static IType::Ptr class_;
			static INode::Ptr parentNode_;
			static INode::Ptr validNode_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_OBJECT_H */