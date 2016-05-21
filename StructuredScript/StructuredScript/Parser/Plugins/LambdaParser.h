#pragma once

#ifndef STRUCTURED_SCRIPT_LAMBDA_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_LAMBDA_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/EmptyNode.h"
#include "../../Nodes/LambdaNode.h"
#include "../../Nodes/OperatorNode.h"
#include "../../Nodes/DeclarationNode.h"

namespace StructuredScript{
	namespace Parser{
		class LambdaParser : public IParserPlugin{
		public:
			explicit LambdaParser(INode::Ptr captures)
				: captures_(captures){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr parseParameters_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception);

			INode::Ptr parseDefinition_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception);

			INode::Ptr captures_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_LAMBDA_PARSER_PLUGIN_H */