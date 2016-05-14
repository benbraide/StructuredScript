#include "GroupParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::GroupParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto next = scanner.next(well).value();
	if (!next.empty()){
		switch (next[0]){
		case '(':
			return parse_(well, scanner, parser, exception, "()", next.size() == 2u);
		case '[':
			return parse_(well, scanner, parser, exception, "[]", next.size() == 2u);
		case '{':
			return parse_(well, scanner, parser, exception, "{}", next.size() == 2u);
		default:
			break;
		}
	}

	return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
		"Expected '(', '[', or '{'!"));
}

StructuredScript::INode::Ptr StructuredScript::Parser::GroupParser::parse_(ICharacterWell &well, IScanner &scanner, IParser &parser,
	IExceptionManager *exception, const std::string &symbol, bool unary){
	if (node_ == nullptr){
		if (unary)
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + symbol + "': Bad expression!"));

		if (!scanner.open(well, symbol[0], symbol[1]))
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("Unexpected error!"));

		auto value = parser.expression(nullptr, well, scanner, exception);
		if (!scanner.close(well)){
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + symbol.substr(0, 1) + value->str() + "...': Bad expression!"));
		}
		else if (Query::ExceptionManager::has(exception))
			return nullptr;

		switch (symbol[0]){
		case '('://Grouped expression
			return std::make_shared<Nodes::GroupNode>(value);
		case '['://List | Attributes
			return std::make_shared<Nodes::IndexNode>(value);
		default://Block
			break;
		}

		return std::make_shared<Nodes::BlockNode>(value);
	}

	if (Query::Node::isDeclaration(node_)){
		if (Query::Node::isInitialization(node_)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + node_->str() + symbol.substr(0, 1) + "': Bad expression!"));
		}

		if (unary)//Save symbol
			scanner.save(Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, symbol));

		INode::Ptr value;
		switch (symbol[0]){
		case '('://Function declaration | definition
			value = FunctionParser(node_).parse(well, scanner, parser, exception);
			break;
		case '['://Array declaration
			break;
		default://Property definition
			break;
		}
		
		return Query::ExceptionManager::has(exception) ? nullptr : value;
	}

	IOperatorInfo::MatchedListType list;
	info_->find(symbol, OperatorType(OperatorType::BINARY | OperatorType::RIGHT_UNARY), list);

	IOperatorInfo::MatchedListType::iterator info;
	if (unary)
		info = list.find(OperatorType(OperatorType::RIGHT_UNARY));
	else
		info = list.find(OperatorType(OperatorType::BINARY));

	if (info->second.precedence < precedence_ || (info->second.precedence == precedence_ && info->second.isLeftAssociative)){//Don't stack
		if (unary)//Save symbol
			scanner.save(Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, symbol));
		
		return node_;
	}

	if (!unary){//Binary with group content as right operand
		scanner.open(well, symbol[0], symbol[1]);
		auto right = parser.expression(nullptr, well, scanner, exception);
		if (!scanner.close(well) && !Query::ExceptionManager::has(exception)){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				"'" + node_->str() + symbol.substr(0, 1) + right->str() + "...': Bad expression!"));
		}
		
		return Query::ExceptionManager::has(exception) ? nullptr : std::make_shared<Nodes::BinaryOperatorNode>(symbol, node_, right);
	}

	return std::make_shared<Nodes::UnaryOperatorNode>(false, symbol, node_);
}
