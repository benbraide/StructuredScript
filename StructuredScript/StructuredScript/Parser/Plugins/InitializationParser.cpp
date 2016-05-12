#include "InitializationParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::InitializationParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	scanner.fork(",;");//Seperate multiple declarations
	auto value = parser.expression(nullptr, well, scanner, exception);

	scanner.close(well, true);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (Query::Node::isEmpty(value))
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + declaration_->str() + " =': Bad expression!"));

	return std::make_shared<Nodes::InitializationNode>(declaration_, value);
}
