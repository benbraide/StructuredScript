#pragma once

#ifndef STRUCTURED_SCRIPT_PARSER_H
#define STRUCTURED_SCRIPT_PARSER_H

#include "../Common/OperatorInfo.h"

#include "../Interfaces/IParser.h"

#include "Plugins/TypenameParser.h"
#include "Plugins/DeclarationParser.h"
#include "Plugins/MemoryStateParser.h"

#include "../Scanner/Scanner.h"
#include "../Scanner/Plugins/Number/SignedNumber.h"

#include "../Nodes/LiteralNode.h"
#include "../Nodes/BlockPairNode.h"
#include "../Nodes/EmptyNode.h"
#include "../Nodes/IdentifierNode.h"

namespace StructuredScript{
	namespace Parser{
		class Parser : public IParser{
		public:
			typedef std::map< std::string, std::shared_ptr<IParserPlugin> > PluginListType;

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception, bool single = false) override;

			virtual INode::Ptr term(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception) override;

			virtual INode::Ptr expression(INode::Ptr node, ICharacterWell &well, IScanner &scanner, IExceptionManager *exception, short precedence = -1) override;

			static void init();

			static OperatorInfo operatorInfo;

		private:
			Scanner::Plugins::SignedNumber signedNumber_;

			static PluginListType plugins_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PARSER_H */