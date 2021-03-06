#pragma once

#ifndef STRUCTURED_SCRIPT_ENUM_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_ENUM_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/EnumNode.h"

namespace StructuredScript{
	namespace Parser{
		class EnumParser : public IParserPlugin{
		public:
			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ENUM_PARSER_PLUGIN_H */