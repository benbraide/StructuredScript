#pragma once

#ifndef STRUCTURED_SCRIPT_DEPENDENT_DECLARATION_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_DEPENDENT_DECLARATION_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"

#include "../../Nodes/DeclarationNode.h"
#include "../../Nodes/OperatorNode.h"

namespace StructuredScript{
	namespace Parser{
		class DependentDeclarationParser : public IParserPlugin{
		public:
			DependentDeclarationParser(INode::Ptr declaration)
				: declaration_(declaration){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr declaration_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_DEPENDENT_DECLARATION_PARSER_PLUGIN_H */