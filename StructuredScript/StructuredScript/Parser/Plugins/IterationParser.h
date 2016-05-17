#pragma once

#ifndef STRUCTURED_SCRIPT_ITERATION_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_ITERATION_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/IterationNode.h"

#include "SelectionParser.h"
#include "../../Scanner/Plugins/Number/SignedNumber.h"

namespace StructuredScript{
	namespace Parser{
		class IterationParser : public IParserPlugin{
		public:
			explicit IterationParser(const std::string &name)
				: name_(name){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr parsePredicate_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception);

			INode::Ptr parseValue_(INode::Ptr predicate, ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception);

			INode::Ptr parseBlock_(INode::Ptr predicate, ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception);

			std::string name_;

			static Scanner::Plugins::SignedNumber signedNumber_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ITERATION_PARSER_PLUGIN_H */