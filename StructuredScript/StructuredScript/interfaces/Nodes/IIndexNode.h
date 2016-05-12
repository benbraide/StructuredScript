#pragma once

#ifndef STRUCTURED_SCRIPT_INDEX_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_INDEX_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class IndexNode{
		public:
			virtual ~IndexNode(){}

			virtual Node::Ptr value() = 0;
		};
	}

	typedef Interfaces::IndexNode IIndexNode;
}

#endif /* !STRUCTURED_SCRIPT_INDEX_NODE_INTERFACE_H */