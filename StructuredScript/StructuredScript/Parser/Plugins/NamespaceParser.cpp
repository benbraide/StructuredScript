#include "NamespaceParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::NamespaceParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto name = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
		switch (next.type()){
		case Scanner::TokenType::TOKEN_TYPE_IDENTIFIER:
			return true;
		default:
			break;
		}

		return (next.value() == "::");
	});

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (!scanner.open(well, '{', '}')){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'namespace...': Bad expression!"));
	}

	auto value = parser.parse(well, scanner, exception);
	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'namespace{...': Bad expression!"));
	}

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::NamespaceNode>(name, value);
}
