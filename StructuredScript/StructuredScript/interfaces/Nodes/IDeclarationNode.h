#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARATION_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_DECLARATION_NODE_INTERFACE_H

#include "../INode.h"
#include "../../Storage/MemoryAttributes.h"

namespace StructuredScript{
	namespace Interfaces{
		class DeclarationNode{
		public:
			virtual ~DeclarationNode(){}

			virtual Memory::Ptr allocate(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Node::Ptr type() = 0;

			virtual Node::Ptr value() = 0;

			virtual void states(unsigned short value) = 0;

			virtual unsigned short states() = 0;

			virtual void attributes(const StructuredScript::Storage::MemoryAttributes &value) = 0;

			virtual MemoryAttributes *attributes() = 0;
		};

		class InitializationNode{
		public:
			virtual ~InitializationNode(){}
		};
	}

	typedef Interfaces::DeclarationNode		IDeclarationNode;
	typedef Interfaces::InitializationNode	IInitializationNode;
}

#endif /* !STRUCTURED_SCRIPT_DECLARATION_NODE_INTERFACE_H */