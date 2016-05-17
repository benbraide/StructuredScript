#pragma once

#ifndef STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class BlockNode{
		public:
			virtual ~BlockNode(){}
		};

		class PlainBlockNode{
		public:
			virtual ~PlainBlockNode(){}

			virtual Node::Ptr value() = 0;
		};
	}

	typedef Interfaces::BlockNode		IBlockNode;
	typedef Interfaces::PlainBlockNode	IPlainBlockNode;
}

#endif /* !STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H */