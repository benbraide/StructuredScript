#pragma once

#ifndef STRUCTURED_SCRIPT_PARSER_H
#define STRUCTURED_SCRIPT_PARSER_H

#include "../Common/OperatorInfo.h"

#include "../Interfaces/IParser.h"

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
			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception, bool single = false) override;

			static OperatorInfo operatorInfo;

		private:
			INode::Ptr term_(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception);

			INode::Ptr expression_(INode::Ptr node, ICharacterWell &well, IScanner &scanner, IExceptionManager *exception, short precedence = -1);

			Scanner::Plugins::SignedNumber signedNumber_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PARSER_H */