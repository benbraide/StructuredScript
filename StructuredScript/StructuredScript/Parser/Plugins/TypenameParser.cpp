#include "TypenameParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::TypenameParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
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

	if (Query::Node::isEmpty(value)){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'typename': Missing identifer!"));
	}

	return std::make_shared<Nodes::TypenameIdentifierNode>(value);
}
