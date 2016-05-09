#pragma once

#ifndef STRUCTURED_SCRIPT_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_NODE_INTERFACE_H

#include "IMemory.h"

namespace StructuredScript{
	namespace Interfaces{
		class Node : protected std::enable_shared_from_this<Node>{
		public:
			typedef std::shared_ptr<Node> Ptr;

			virtual ~Node(){}

			virtual Ptr ptr() = 0;

			virtual Ptr clone() = 0;

			virtual Any::Ptr evaluate(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual std::string str() = 0;
		};
	}

	typedef Interfaces::Node INode;
}

#endif /* !STRUCTURED_SCRIPT_NODE_INTERFACE_H */