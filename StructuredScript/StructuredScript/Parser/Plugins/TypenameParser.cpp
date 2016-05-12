#include "TypenameParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::TypenameParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto value = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
		return (next.type() == Scanner::TokenType::TOKEN_TYPE_IDENTIFIER || next.value() == "::");
	});

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::TypenameIdentifierNode>(value);
}
