#pragma once

#ifndef STRUCTURED_SCRIPT_EXCEPTION_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_EXCEPTION_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/ExceptionNode.h"
#include "../../Nodes/DeclarationNode.h"

#include "../../Scanner/Plugins/Number/SignedNumber.h"

namespace StructuredScript{
	namespace Parser{
		class ExceptionParser : public IParserPlugin{
		public:
			ExceptionParser(const std::string &name, bool matched = false)
				: name_(name), matched_(matched){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr parsePredicate_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception);

			INode::Ptr parseValue_(INode::Ptr predicate, ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception);

			std::string name_;
			bool matched_;

			static Scanner::Plugins::SignedNumber signedNumber_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_EXCEPTION_PARSER_PLUGIN_H */