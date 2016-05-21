#include "AtSymbolParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::AtSymbolParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	if (well.peek() == '['){//Attributes
		if (!scanner.open(well, '[', ']'))//Declaration
			return nullptr;

		auto value = parser.parse(well, scanner, exception);
		if (!scanner.close(well)){
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'@[" + value->str() + "...': Bad expression!"));
		}
		else if (Query::ExceptionManager::has(exception))
			return nullptr;

		scanner.fork(';');//Single line
		auto target = parser.expression(nullptr, well, scanner, exception, -1, validator_);

		scanner.close(well, true);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		Storage::MemoryAttributes::ListType attributes;
		if (!Storage::MemoryAttributes::parse(value, target, attributes)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'@[" + value->str() + "]': One or more attributes are invalid or can't be applied to the target node!"));
		}

		target->attributes(std::make_shared<Storage::MemoryAttributes>(attributes));
		return target;
	}

	auto next = scanner.next(well);
	auto type = next.type();
	if (type != Scanner::TokenType::TOKEN_TYPE_IDENTIFIER && type != Scanner::Plugins::TypenameTokenType::type){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'@" + next.value() + "': Bad expression!"));
	}

	return std::make_shared<Nodes::IdentifierNode>(next.value());
}
