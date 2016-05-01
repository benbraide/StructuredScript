#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_OPERATOR_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class OperatorNode{
		public:
			typedef std::shared_ptr<Node> Ptr;

			virtual ~OperatorNode(){}

			virtual std::string getOperator() const = 0;
		};

		class LeftUnaryOperatorNode : public OperatorNode{
		public:
			virtual ~LeftUnaryOperatorNode(){}

			virtual Ptr getOperand() const = 0;
		};

		class RightUnaryOperatorNode : public OperatorNode{
		public:
			virtual ~RightUnaryOperatorNode(){}

			virtual Ptr getOperand() const = 0;
		};

		class BinaryOperatorNode : public OperatorNode{
		public:
			virtual ~BinaryOperatorNode(){}

			virtual Ptr getLeftOperand() const = 0;

			virtual Ptr getRightOperand() const = 0;
		};
	}

	typedef Interfaces::OperatorNode			IOperatorNode;
	typedef Interfaces::LeftUnaryOperatorNode	ILeftUnaryOperatorNode;
	typedef Interfaces::RightUnaryOperatorNode	IRightUnaryOperatorNode;
	typedef Interfaces::BinaryOperatorNode		IBinaryOperatorNode;
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_NODE_INTERFACE_H */