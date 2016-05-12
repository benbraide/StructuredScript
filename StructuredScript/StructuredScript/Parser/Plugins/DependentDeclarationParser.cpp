#include "DependentDeclarationParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::DependentDeclarationParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	scanner.fork(",=;");//Seperate multiple declarations | initializations
	auto value = parser.expression(nullptr, well, scanner, exception);

	scanner.close(well, true);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (Query::Node::isEmpty(value))
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + declaration_->str() + " =': Bad expression!"));

	if (Query::Node::isDeclaration(value))//Possibly multiple parameter declarations
		return std::make_shared<Nodes::BinaryOperatorNode>(",", declaration_, value);

	return std::make_shared<Nodes::DependentDeclarationNode>(declaration_, value);
}
