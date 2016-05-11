#pragma once

#ifndef STRUCTURED_SCRIPT_BLOCK_PAIR_NODE_H
#define STRUCTURED_SCRIPT_BLOCK_PAIR_NODE_H

#include "OperatorNode.h"

namespace StructuredScript{
	namespace Nodes{
		class BlockPairNode : public BinaryOperatorNode{
		public:
			BlockPairNode(Ptr leftOperand, Ptr rightOperand)
				: BinaryOperatorNode(";", leftOperand, rightOperand){}

			virtual Ptr clone() override;

			virtual std::string str() override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_BLOCK_PAIR_NODE_H */