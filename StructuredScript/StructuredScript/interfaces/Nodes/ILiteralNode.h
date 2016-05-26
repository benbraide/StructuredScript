#pragma once

#ifndef STRUCTURED_SCRIPT_LITERAL_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_LITERAL_NODE_INTERFACE_H

#include "../../Scanner/Token.h"

namespace StructuredScript{
	namespace Interfaces{
		class LiteralNode{
		public:
			virtual ~LiteralNode(){}

			virtual void value(const Scanner::Token &value) = 0;

			virtual Scanner::Token value() = 0;
		};
	}

	typedef Interfaces::LiteralNode ILiteralNode;
}

#endif /* !STRUCTURED_SCRIPT_LITERAL_NODE_INTERFACE_H */