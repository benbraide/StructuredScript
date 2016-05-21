#pragma once

#ifndef STRUCTURED_SCRIPT_AT_SYMBOL_PARSER_H
#define STRUCTURED_SCRIPT_AT_SYMBOL_PARSER_H

#include "../../Common/ExceptionManagerQuery.h"
#include "../../Common/Factory.h"

#include "../../Interfaces/IParserPlugin.h"
#include "../../Storage/MemoryAttributes.h"
#include "../../Scanner/Plugins/Identifier/TypenameIdentifier.h"

#include "../../Nodes/IdentifierNode.h"

namespace StructuredScript{
	namespace Parser{
		class AtSymbolParser : public IParserPlugin{
		public:
			AtSymbolParser(IParser::Validator validator)
				: validator_(validator){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			IParser::Validator validator_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_AT_SYMBOL_PARSER_H */