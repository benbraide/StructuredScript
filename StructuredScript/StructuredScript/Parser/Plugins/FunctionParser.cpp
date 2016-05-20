#include "FunctionParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::FunctionParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto parameters = parseParameters_(well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;
	
	auto definition = parseDefinition_(parameters, well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (definition == nullptr)//Declaration
		return std::make_shared<Nodes::FunctionDeclarationNode>(declaration_, parameters);

	return std::make_shared<Nodes::FunctionDefinitionNode>(declaration_, parameters, definition);
}

StructuredScript::INode::Ptr StructuredScript::Parser::FunctionParser::parseConstructor(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto parameters = parseParameters_(well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	INode::Ptr initializers;
	if (scanner.peek(well).value() == ":"){//Initializers
		scanner.next(well);//Ignore

		initializers = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
			auto value = next.value();
			return (value != "{" && value != ";");
		});

		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	auto definition = parseDefinition_(parameters, well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	Nodes::ConstructorNode::InitializerListType list;
	if (initializers != nullptr){
		Nodes::ConstructorNode::parseInitializers(initializers, list, exception, nullptr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	if (definition == nullptr)//Declaration
		return std::make_shared<Nodes::ConstructorDeclarationNode>(declaration_, parameters, list);

	return std::make_shared<Nodes::ConstructorDefinitionNode>(declaration_, parameters, list, definition);
}

StructuredScript::INode::Ptr StructuredScript::Parser::FunctionParser::parseDestructor(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto parameters = parseParameters_(well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (!Query::Node::isEmpty(parameters)){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + declaration_->str() + "(" + parameters->str() + "){...': Destructor cannot have parameters!"));
	}

	auto definition = parseDefinition_(parameters, well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (definition == nullptr)//Declaration
		return std::make_shared<Nodes::DestructorDeclarationNode>(declaration_, parameters);

	return std::make_shared<Nodes::DestructorDefinitionNode>(declaration_, parameters, definition);
}

StructuredScript::INode::Ptr StructuredScript::Parser::FunctionParser::parseParameters_(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
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
						"'" + declaration_->str() + "(" + parameters->str() + ",...': Bad expression!"));
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
				"'" + declaration_->str() + "(" + parameters->str() + "...': Bad expression!"));
		}
	}
	else{//No parameters
		scanner.next(well);//Ignore
		parameters = std::make_shared<Nodes::EmptyNode>();
	}

	return parameters;
}

StructuredScript::INode::Ptr StructuredScript::Parser::FunctionParser::parseDefinition_(INode::Ptr parameters, ICharacterWell &well, IScanner &scanner,
	IParser &parser, IExceptionManager *exception){
	if (!scanner.open(well, '{', '}'))//Declaration
		return nullptr;

	auto definition = parser.parse(well, scanner, exception);
	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + declaration_->str() + "(" + parameters->str() + "){...': Bad expression!"));
	}
	else if (Query::ExceptionManager::has(exception))
		return nullptr;

	return definition;
}
