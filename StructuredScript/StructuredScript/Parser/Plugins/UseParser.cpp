#include "UseParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::UseParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	bool useStorage;
	if (scanner.peek(well).value() == "namespace"){
		useStorage = true;
		scanner.next(well);//Ignore
	}
	else
		useStorage = false;

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
		if (useStorage){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'using namespace': Missing identifer!"));
		}

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'using': Missing identifer!"));
	}

	return std::make_shared<Nodes::UseNode>(value, useStorage);
}
