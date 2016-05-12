#pragma once

#ifndef STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class BlockNode{
		public:
			virtual ~BlockNode(){}

			virtual Node::Ptr value() = 0;
		};
	}

	typedef Interfaces::BlockNode IBlockNode;
}

#endif /* !STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H */