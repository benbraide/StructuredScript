#pragma once

#ifndef STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H

#include <string>

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class IdentifierNode{
		public:
			virtual ~IdentifierNode(){}

			virtual std::string value() const = 0;
		};

		class IdentifierExpressionNode{
		public:
			virtual ~IdentifierExpressionNode(){}
		};

		class OperatorIdentifierNode{
		public:
			virtual ~OperatorIdentifierNode(){}

			virtual Node::Ptr nodeValue() = 0;
		};

		class TypeIdentifierNode{
		public:
			virtual ~TypeIdentifierNode(){}
		};
	}

	typedef Interfaces::IdentifierNode				IIdentifierNode;
	typedef Interfaces::IdentifierExpressionNode	IIdentifierExpressionNode;
	typedef Interfaces::OperatorIdentifierNode		IOperatorIdentifierNode;
	typedef Interfaces::TypeIdentifierNode			ITypeIdentifierNode;
}

#endif /* !STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H */