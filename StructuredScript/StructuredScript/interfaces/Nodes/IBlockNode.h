#pragma once

#ifndef STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H

namespace StructuredScript{
	namespace Interfaces{
		class BlockNode{
		public:
			virtual ~BlockNode(){}
		};
	}

	typedef Interfaces::BlockNode IBlockNode;
}

#endif /* !STRUCTURED_SCRIPT_BLOCK_NODE_INTERFACE_H */