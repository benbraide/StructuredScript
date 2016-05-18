#pragma once

#ifndef STRUCTURED_SCRIPT_USE_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_USE_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/UseNode.h"
#include "../../Scanner/Plugins/Identifier/TypenameIdentifier.h"

namespace StructuredScript{
	namespace Parser{
		class UseParser : public IParserPlugin{
		public:
			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_USE_PARSER_PLUGIN_H */