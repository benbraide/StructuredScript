#pragma once

#ifndef STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H

namespace StructuredScript{
	namespace Interfaces{
		class IdentifierNode{
		public:
			virtual ~IdentifierNode(){}
		};
	}

	typedef Interfaces::IdentifierNode IIdentifierNode;
}

#endif /* !STRUCTURED_SCRIPT_IDENTIFIER_NODE_INTERFACE_H */