#pragma once

#ifndef STRUCTURED_SCRIPT_PARSER_H
#define STRUCTURED_SCRIPT_PARSER_H

#include "../Common/OperatorInfo.h"

#include "../Interfaces/IParser.h"

#include "Plugins/TypenameParser.h"
#include "Plugins/DeclarationParser.h"
#include "Plugins/InitializationParser.h"
#include "Plugins/DependentDeclarationParser.h"
#include "Plugins/DeclaredTypeParser.h"
#include "Plugins/GroupParser.h"
#include "Plugins/SourceParser.h"
#include "Plugins/ExpressionParser.h"
#include "Plugins/AtSymbolParser.h"
#include "Plugins/SelectionParser.h"
#include "Plugins/ConditionalParser.h"
#include "Plugins/IterationParser.h"

#include "../Scanner/Scanner.h"
#include "../Scanner/Plugins/Number/SignedNumber.h"

#include "../Nodes/LiteralNode.h"
#include "../Nodes/BlockPairNode.h"
#include "../Nodes/EmptyNode.h"
#include "../Nodes/IdentifierNode.h"
#include "../Nodes/InterruptNode.h"
#include "../Nodes/EchoNode.h"
#include "../Nodes/ThrowNode.h"

#include "../Storage/MemoryAttributes.h"

namespace StructuredScript{
	namespace Parser{
		class Parser : public IParser{
		public:
			typedef std::map< std::string, std::shared_ptr<IParserPlugin> > PluginListType;

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception,
				Validator validator = nullptr, bool single = false) override;

			virtual INode::Ptr term(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception, Validator validator = nullptr) override;

			virtual INode::Ptr expression(INode::Ptr node, ICharacterWell &well, IScanner &scanner, IExceptionManager *exception,
				short precedence = -1, Validator validator = nullptr) override;

			static void init();

			static OperatorInfo operatorInfo;

		private:
			static Scanner::Plugins::SignedNumber signedNumber_;
			static PluginListType plugins_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PARSER_H */