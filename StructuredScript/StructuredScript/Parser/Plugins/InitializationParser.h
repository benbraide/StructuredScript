#pragma once

#ifndef STRUCTURED_SCRIPT_INITIALIZATION_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_INITIALIZATION_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/DeclarationNode.h"

namespace StructuredScript{
	namespace Parser{
		class InitializationParser : public IParserPlugin{
		public:
			InitializationParser(INode::Ptr declaration)
				: declaration_(declaration){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			INode::Ptr declaration_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_INITIALIZATION_PARSER_PLUGIN_H */