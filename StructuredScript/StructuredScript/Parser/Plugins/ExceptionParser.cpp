#include "ExceptionParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::ExceptionParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	if (name_ == "catch"){
		if (!matched_){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'catch': Found without matching try block!"));
		}

		auto predicate = parsePredicate_(well, scanner, parser, exception);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		auto value = parseValue_(predicate, well, scanner, parser, exception);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		INode::Ptr nextNode;
		auto next = scanner.peek(well, { &signedNumber_ }).value();
		if (next == "catch" || next == "finally"){
			scanner.next(well);//Ignore

			nextNode = ExceptionParser(next, true).parse(well, scanner, parser, exception);
			if (Query::ExceptionManager::has(exception))
				return nullptr;
		}

		return std::make_shared<Nodes::CatchNode>(predicate, value, nextNode);
	}

	auto value = parseValue_(nullptr, well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (name_ == "try"){
		auto next = scanner.peek(well, { &signedNumber_ }).value();
		if (next != "catch" && next != "finally"){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'try': Found without accompanying 'catch' or 'finally' block!"));
		}

		scanner.next(well);//Ignore
		auto handler = ExceptionParser(next, true).parse(well, scanner, parser, exception);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return std::make_shared<Nodes::TryNode>(handler, value);
	}

	return std::make_shared<Nodes::FinallyNode>(value);
}

StructuredScript::INode::Ptr StructuredScript::Parser::ExceptionParser::parsePredicate_(ICharacterWell &well, IScanner &scanner, IParser &parser,
	IExceptionManager *exception){
	if (!scanner.open(well, '(', ')')){//Extract parameters
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + name_ + "...': Bad expression!"));
	}

	auto predicate = parser.expression(nullptr, well, scanner, exception);
	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + name_ + "(" + predicate->str() + "...': Bad expression!"));
	}

	if (!Query::Node::isDeclaration(predicate)){
		if (!Query::Node::isIdentifier(predicate) || Query::Node::isOperatorIdentifier(predicate)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + name_ + "(" + predicate->str() + "...': Expected a declaration!"));
		}

		predicate = std::make_shared<Nodes::DeclarationNode>(predicate, nullptr);//Unnamed
	}

	return predicate;
}

StructuredScript::INode::Ptr StructuredScript::Parser::ExceptionParser::parseValue_(INode::Ptr predicate, ICharacterWell &well, IScanner &scanner,
	IParser &parser, IExceptionManager *exception){
	if (!scanner.open(well, '{', '}')){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + name_ + "...': Bad expression!"));
	}

	auto value = parser.parse(well, scanner, exception);
	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (predicate == nullptr){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + name_ + "{...': Bad expression!"));
		}

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + name_ + "(" + predicate->str() + "){...': Bad expression!"));
	}

	return value;
}

StructuredScript::Scanner::Plugins::SignedNumber StructuredScript::Parser::ExceptionParser::signedNumber_;
