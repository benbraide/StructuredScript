#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_OPERATOR_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/IdentifierNode.h"
#include "../../Scanner/Plugins/Identifier/TypenameIdentifier.h"

namespace StructuredScript{
	namespace Parser{
		class OperatorParser : public IParserPlugin{
		public:
			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_PARSER_PLUGIN_H */