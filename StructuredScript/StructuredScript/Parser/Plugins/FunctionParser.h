#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_FUNCTION_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/FunctionNode.h"
#include "../../Nodes/OperatorNode.h"
#include "../../Nodes/DeclarationNode.h"

namespace StructuredScript{
	namespace Parser{
		class FunctionParser : public IParserPlugin{
		public:
			FunctionParser(INode::Ptr declaration)
				: declaration_(declaration){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr declaration_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_PARSER_PLUGIN_H */