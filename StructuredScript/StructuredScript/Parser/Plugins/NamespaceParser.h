#pragma once

#ifndef STRUCTURED_SCRIPT_NAMESPACE_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_NAMESPACE_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/NamespaceNode.h"

namespace StructuredScript{
	namespace Parser{
		class NamespaceParser : public IParserPlugin{
		public:
			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NAMESPACE_PARSER_PLUGIN_H */