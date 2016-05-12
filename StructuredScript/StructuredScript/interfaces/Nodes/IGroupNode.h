#pragma once

#ifndef STRUCTURED_SCRIPT_GROUP_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_GROUP_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class GroupNode{
		public:
			virtual ~GroupNode(){}

			virtual Node::Ptr value() = 0;
		};
	}

	typedef Interfaces::GroupNode IGroupNode;
}

#endif /* !STRUCTURED_SCRIPT_GROUP_NODE_INTERFACE_H */