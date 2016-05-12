#pragma once

#ifndef STRUCTURED_SCRIPT_PARSER_PLUGIN_INTERFACE_H
#define STRUCTURED_SCRIPT_PARSER_PLUGIN_INTERFACE_H

#include "IParser.h"

namespace StructuredScript{
	namespace Interfaces{
		class ParserPlugin{
		public:
			virtual Node::Ptr parse(CharacterWell &well, Scanner &scanner, Parser &parser, ExceptionManager *exception) = 0;
		};
	}

	typedef Interfaces::ParserPlugin IParserPlugin;
}

#endif /* !STRUCTURED_SCRIPT_PARSER_PLUGIN_INTERFACE_H */