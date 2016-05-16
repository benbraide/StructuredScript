#pragma once

#ifndef STRUCTURED_SCRIPT_GROUP_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_GROUP_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Interfaces/IOperatorInfo.h"

#include "../../Nodes/GroupNode.h"
#include "../../Nodes/IndexNode.h"
#include "../../Nodes/BlockNode.h"
#include "../../Nodes/PropertyNode.h"
#include "../../Nodes/DeclarationNode.h"

#include "FunctionParser.h"

namespace StructuredScript{
	namespace Parser{
		class GroupParser : public IParserPlugin{
		public:
			GroupParser(INode::Ptr node, IOperatorInfo &info, short precedence)
				: node_(node), info_(&info), precedence_(precedence){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr parse_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception, const std::string &symbol, bool unary);

			INode::Ptr parseArray_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception, bool unary);

			INode::Ptr parseProperty_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception, bool unary);

			INode::Ptr node_;
			IOperatorInfo *info_;
			short precedence_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_GROUP_PARSER_PLUGIN_H */