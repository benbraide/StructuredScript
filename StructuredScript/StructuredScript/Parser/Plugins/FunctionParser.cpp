#include "FunctionParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::FunctionParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	INode::Ptr parameters;
	if (scanner.peek(well).value() != "()"){
		if (!scanner.open(well, '(', ')')){//Extract parameters
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + declaration_->str() + "...': Bad expression!"));
		}

		do{
			if (parameters != nullptr)//Skip ','
				scanner.next(well);

			auto node = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
				return (next.value() != ",");
			});

			if (!Query::Node::isDeclaration(node)){//Check unnamed parameter
				if (!Query::Node::isIdentifier(node) || Query::Node::isOperatorIdentifier(node)){
					return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
						"'" + node->str() + "': Expected function parameter to be a declaration!"));
				}

				node = std::make_shared<Nodes::DeclarationNode>(node, nullptr);//Unnamed
			}

			if (parameters != nullptr){
				if (Query::Node::isEmpty(node)){//Trailing ','
					return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
						"'" + declaration_->str() + "(" + parameters->str() + ",...': Bad expression!"));
				}

				parameters = std::make_shared<Nodes::BinaryOperatorNode>(",", parameters, node);//Append node to parameter list
			}
			else
				parameters = node;

		} while (scanner.peek(well).value() == ",");

		if (!scanner.close(well)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + declaration_->str() + "(" + parameters->str() + "...': Bad expression!"));
		}
	}
	else{//No parameters
		scanner.next(well);//Ignore
		parameters = std::make_shared<Nodes::EmptyNode>();
	}

	if (!scanner.open(well, '{', '}'))//Declaration
		return std::make_shared<Nodes::FunctionDeclarationNode>(declaration_, parameters);

	auto definition = parser.parse(well, scanner, exception);
	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + declaration_->str() + "(" + parameters->str() + "){...': Bad expression!"));
	}
	else if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::FunctionDefinitionNode>(declaration_, parameters, definition);
}
