#pragma once

#ifndef STRUCTURED_SCRIPT_NODE_OBJECT_H
#define STRUCTURED_SCRIPT_NODE_OBJECT_H

#include "Primitive.h"
#include "PrimitiveObject.h"

#include "../Common/ExceptionManager.h"

namespace StructuredScript{
	namespace Objects{
		class NodeObject : public Primitive, public PrimitiveObject, public INodeObject{
		public:
			explicit NodeObject(INode::Ptr value)
				: Primitive(class_), Objects::PrimitiveObject(class_, Primitive::memory_), value_(value){}

			NodeObject(INode::Ptr value, IType::Ptr type)
				: Primitive(type), Objects::PrimitiveObject(type, Primitive::memory_), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual INode::Ptr value() override;

			static void init();

		protected:
			INode::Ptr value_;

			static IType::Ptr class_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NODE_OBJECT_H */