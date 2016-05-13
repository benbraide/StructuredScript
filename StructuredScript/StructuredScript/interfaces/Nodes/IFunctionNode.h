#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_FUNCTION_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class FunctionNode{
		public:
			virtual ~FunctionNode(){}

			virtual Node::Ptr type() = 0;

			virtual Node::Ptr name() = 0;

			virtual Node::Ptr parameters() = 0;
		};

		class FunctionDeclarationNode{
		public:
			virtual ~FunctionDeclarationNode(){}
		};

		class FunctionDefinitionNode{
		public:
			virtual ~FunctionDefinitionNode(){}

			virtual Node::Ptr definition() = 0;
		};
	}

	typedef Interfaces::FunctionNode			IFunctionNode;
	typedef Interfaces::FunctionDeclarationNode	IFunctionDeclarationNode;
	typedef Interfaces::FunctionDefinitionNode	IFunctionDefinitionNode;
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_NODE_INTERFACE_H */