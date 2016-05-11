#pragma once

#ifndef STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H

#include <string>

namespace StructuredScript{
	namespace Interfaces{
		class IdentifierNode{
		public:
			virtual ~IdentifierNode(){}

			virtual std::string value() const = 0;
		};

		class TypeIdentifierNode{
		public:
			virtual ~TypeIdentifierNode(){}
		};
	}

	typedef Interfaces::IdentifierNode		IIdentifierNode;
	typedef Interfaces::TypeIdentifierNode	ITypeIdentifierNode;
}

#endif /* !STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H */