#include "LambdaParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::LambdaParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto parameters = parseParameters_(well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	INode::Ptr type;
	if (scanner.peek(well).value() == "->"){//Return type
		scanner.next(well);//Ignore

		type = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
			auto value = next.value();
			return (value != "{" && value != ";");
		});

		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (Query::Node::isEmpty(type)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'[" + captures_->str() + "](...) ->': Bad expression!"));
		}
	}

	auto definition = parseDefinition_(well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::LambdaNode>(captures_, parameters, type, definition);
}

StructuredScript::INode::Ptr StructuredScript::Parser::LambdaParser::parseParameters_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	INode::Ptr parameters;
	if (scanner.peek(well).value() != "()"){
		if (!scanner.open(well, '(', ')'))//Extract parameters
			return nullptr;//No parameters

		do{
			if (parameters != nullptr)//Skip ','
				scanner.next(well);

			auto node = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
				return (next.value() != ",");
			});

			if (Query::ExceptionManager::has(exception))
				return nullptr;

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
						"'[" + captures_->str() + "](" + parameters->str() + ",...': Bad expression!"));
				}

				parameters = std::make_shared<Nodes::BinaryOperatorNode>(",", parameters, node);//Append node to parameter list
			}
			else
				parameters = node;

		} while (scanner.peek(well).value() == ",");

		if (!scanner.close(well)){
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'[" + captures_->str() + "](" + parameters->str() + "...': Bad expression!"));
		}
	}
	else{//No parameters
		scanner.next(well);//Ignore
		parameters = std::make_shared<Nodes::EmptyNode>();
	}

	return parameters;
}

StructuredScript::INode::Ptr StructuredScript::Parser::LambdaParser::parseDefinition_(ICharacterWell &well, IScanner &scanner, IParser &parser,
	IExceptionManager *exception){
	if (!scanner.open(well, '{', '}')){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'[" + captures_->str() + "](...)...': Bad expression!"));
	}

	auto definition = parser.parse(well, scanner, exception);
	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'[" + captures_->str() + "](...){...': Bad expression!"));
	}
	else if (Query::ExceptionManager::has(exception))
		return nullptr;

	return definition;
}
