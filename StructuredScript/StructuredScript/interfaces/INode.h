#pragma once

#ifndef STRUCTURED_SCRIPT_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_NODE_INTERFACE_H

#include "IAny.h"

namespace StructuredScript{
	namespace Interfaces{
		class Node : protected std::enable_shared_from_this<Node>{
		public:
			typedef std::shared_ptr<Node>	Ptr;
			typedef std::shared_ptr<Any>	AnyPtr;

			virtual ~Node(){}

			virtual Ptr ptr() = 0;

			virtual Ptr clone() = 0;

			virtual AnyPtr evaluate(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual std::string str() = 0;
		};
	}

	typedef Interfaces::Node INode;
}

#endif /* !STRUCTURED_SCRIPT_NODE_INTERFACE_H */