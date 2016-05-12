#pragma once

#ifndef STRUCTURED_SCRIPT_PARSER_INTERFACE_H
#define STRUCTURED_SCRIPT_PARSER_INTERFACE_H

#include <functional>

#include "IScanner.h"
#include "INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class Parser{
		public:
			typedef std::function<bool(const Scanner::Token &)> Validator;

			virtual Node::Ptr parse(CharacterWell &well, Scanner &scanner, ExceptionManager *exception,
				Validator validator = nullptr, bool single = false) = 0;

			virtual Node::Ptr term(CharacterWell &well, Scanner &scanner, ExceptionManager *exception, Validator validator = nullptr) = 0;

			virtual Node::Ptr expression(Node::Ptr node, CharacterWell &well, Scanner &scanner, ExceptionManager *exception,
				short precedence = -1, Validator validator = nullptr) = 0;
		};
	}

	typedef Interfaces::Parser IParser;
}

#endif /* !STRUCTURED_SCRIPT_PARSER_INTERFACE_H */