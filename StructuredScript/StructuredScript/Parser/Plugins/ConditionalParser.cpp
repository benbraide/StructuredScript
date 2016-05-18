#include "ConditionalParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::ConditionalParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto value = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
		return (next.value() != ":");
	});

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	scanner.next(well);//Ignore ':'
	auto elseNode = parser.expression(nullptr, well, scanner, exception, precedence_);

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::ConditionalNode>(predicate_, value, elseNode);
}
