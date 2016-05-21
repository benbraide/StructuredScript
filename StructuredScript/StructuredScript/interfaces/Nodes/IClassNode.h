#pragma once

#ifndef STRUCTURED_SCRIPT_CLASS_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_CLASS_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class ClassNode{
		public:
			virtual ~ClassNode(){}

			virtual Type::Ptr create(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual void value(Node::Ptr value) = 0;

			virtual Node::Ptr value() = 0;
		};
	}

	typedef Interfaces::ClassNode IClassNode;
}

#endif /* !STRUCTURED_SCRIPT_CLASS_NODE_INTERFACE_H */