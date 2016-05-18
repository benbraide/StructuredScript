#include "EnumParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::EnumParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto name = parser.term(well, scanner, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (!Query::Node::isIdentifier(name) || Query::Node::isOperatorIdentifier(name) || Query::Node::isTypeIdentifier(name)){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'enum...': Expected an identifier!"));
	}

	if (!scanner.open(well, '{', '}')){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'enum " + name->str() + "...': Bad expression!"));
	}

	auto value = parser.parse(well, scanner, exception);
	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'enum " + name->str() + "{...': Bad expression!"));
	}

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::EnumNode>(name, value);
}
