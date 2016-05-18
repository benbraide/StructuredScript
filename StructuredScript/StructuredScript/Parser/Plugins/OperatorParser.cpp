#include "OperatorParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::OperatorParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	if (scanner.peek(well).type() == Scanner::TokenType::TOKEN_TYPE_SYMBOL)//Use symbol as operator value
		return std::make_shared<Nodes::OperatorIdentifierNode>(std::make_shared<Nodes::IdentifierNode>(scanner.next(well).value()));

	auto value = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
		switch (next.type()){
		case Scanner::TokenType::TOKEN_TYPE_IDENTIFIER:
		case Scanner::Plugins::TypenameTokenType::type:
			return true;
		default:
			break;
		}

		return (next.value() == "::");
	});

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::OperatorIdentifierNode>(value);
}
