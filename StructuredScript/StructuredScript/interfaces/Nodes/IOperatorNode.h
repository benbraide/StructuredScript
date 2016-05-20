#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_OPERATOR_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class OperatorNode{
		public:
			virtual ~OperatorNode(){}

			virtual std::string value() const = 0;
		};

		class UnaryOperatorNode : public OperatorNode{
		public:
			virtual ~UnaryOperatorNode(){}

			virtual std::shared_ptr<Node> operand() = 0;

			virtual bool isLeft() const = 0;
		};

		class BinaryOperatorNode : public OperatorNode{
		public:
			virtual ~BinaryOperatorNode(){}

			virtual std::shared_ptr<Node> leftOperand() = 0;

			virtual std::shared_ptr<Node> rightOperand() = 0;
		};
	}

	typedef Interfaces::OperatorNode			IOperatorNode;
	typedef Interfaces::UnaryOperatorNode		IUnaryOperatorNode;
	typedef Interfaces::BinaryOperatorNode		IBinaryOperatorNode;
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_NODE_INTERFACE_H */