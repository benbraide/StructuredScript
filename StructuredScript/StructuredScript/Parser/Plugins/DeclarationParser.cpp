#include "DeclarationParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::DeclarationParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto value = parser.term(well, scanner, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::DeclarationNode>(type_, value);
}
