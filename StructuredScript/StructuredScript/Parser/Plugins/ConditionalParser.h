#pragma once

#ifndef STRUCTURED_SCRIPT_CONDITIONAL_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_CONDITIONAL_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/SelectionNode.h"

namespace StructuredScript{
	namespace Parser{
		class ConditionalParser : public IParserPlugin{
		public:
			ConditionalParser(INode::Ptr predicate, short precedence)
				: predicate_(predicate), precedence_(precedence){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr predicate_;
			short precedence_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_CONDITIONAL_PARSER_PLUGIN_H */