#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_OBJECT_H
#define STRUCTURED_SCRIPT_FUNCTION_OBJECT_H

#include "Primitive.h"
#include "PrimitiveObject.h"

#include "../Storage/FunctionMemory.h"
#include "../Common/ExceptionManager.h"

namespace StructuredScript{
	namespace Objects{
		class FunctionObject : public Primitive, public PrimitiveObject{
		public:
			typedef StructuredScript::Storage::FunctionMemory::ListType ListType;

			explicit FunctionObject(IMemory::Ptr value);

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			static void init();

		protected:
			Ptr bound_;
			IMemory::Ptr value_;

			static IType::Ptr class_;
			static INode::Ptr lengthNode_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_OBJECT_H */