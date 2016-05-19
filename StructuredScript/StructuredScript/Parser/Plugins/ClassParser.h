#pragma once

#ifndef STRUCTURED_SCRIPT_CLASS_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_CLASS_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/ClassNode.h"
#include "../../Nodes/BlockPairNode.h"
#include "../../Nodes/IdentifierNode.h"

#include "FunctionParser.h"

namespace StructuredScript{
	namespace Parser{
		class ClassParser : public IParserPlugin{
		public:
			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_CLASS_PARSER_PLUGIN_H */