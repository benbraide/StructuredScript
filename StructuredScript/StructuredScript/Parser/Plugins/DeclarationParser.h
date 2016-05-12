#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARATION_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_DECLARATION_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/DeclarationNode.h"

namespace StructuredScript{
	namespace Parser{
		class DeclarationParser : public IParserPlugin{
		public:
			DeclarationParser(INode::Ptr type)
				: type_(type){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr type_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_DECLARATION_PARSER_PLUGIN_H */