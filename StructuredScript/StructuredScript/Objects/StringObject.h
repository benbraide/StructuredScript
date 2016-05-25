#pragma once

#ifndef STRUCTURED_SCRIPT_STRING_OBJECT_H
#define STRUCTURED_SCRIPT_STRING_OBJECT_H

#include "Real.h"

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Types/Type.h"
#include "../Common/Factory.h"

#include "PrimitiveObject.h"

namespace StructuredScript{
	namespace Objects{
		class String : public TypedPrimitive<std::string, Primitive::STRING_RANK>, public PrimitiveObject, public IString{
		public:
			String(const std::string &value);

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			static void init();

		protected:
			virtual IAny::Ptr promote_(Primitive *target) override;

			virtual IAny::Ptr evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr) override;

			static IType::Ptr class_;
			static INode::Ptr lengthNode_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STRING_OBJECT_H */