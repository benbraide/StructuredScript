#include "IterationParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::IterationParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	if (name_ != "do"){// 'for' | 'while'
		auto predicate = parsePredicate_(well, scanner, parser, exception);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		auto value = parseValue_(predicate, well, scanner, parser, exception);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (scanner.peek(well, { &signedNumber_ }).value() == "else"){
			scanner.next(well);//Ignore

			auto elseNode = SelectionParser("else", true).parse(well, scanner, parser, exception);
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			if (name_[0] == 'f')// for...else
				return std::make_shared< Nodes::ControlExtension<Nodes::IfNode> >(elseNode, predicate, value);

			return std::make_shared< Nodes::ControlExtension<Nodes::UnlessNode> >(elseNode, predicate, value);
		}

		if (name_[0] == 'f')
			return std::make_shared<Nodes::ForNode>(predicate, value);

		return std::make_shared<Nodes::WhileNode>(predicate, value);
	}

	if (!scanner.open(well, '{', '}')){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'do...': Bad expression!"));
	}

	auto value = parseBlock_(nullptr, well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	auto next = scanner.next(well);
	if (next.value() != "while"){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'do{...}" + next.value() + "...': Bad expression!"));
	}

	auto predicate = parsePredicate_(well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::DoWhileNode>(predicate, value);
}

StructuredScript::INode::Ptr StructuredScript::Parser::IterationParser::parsePredicate_(ICharacterWell &well,
	IScanner &scanner, IParser &parser, IExceptionManager *exception){
	if (!scanner.open(well, '(', ')')){//Extract parameters
		if (name_[0] == 'd'){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'do{...}while...': Bad expression!"));
		}

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + name_ + "...': Bad expression!"));
	}

	INode::Ptr predicate;
	if (name_[0] != 'f'){// 'while'
		predicate = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
			return (next.value() != ";");
		});
	}
	else// 'for'
		predicate = parser.parse(well, scanner, exception);

	if (!scanner.close(well)){
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (name_[0] == 'd'){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'do{...}while(" + predicate->str() + "...': Bad expression!"));
		}

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + name_ + "(" + predicate->str() + "...': Bad expression!"));
	}

	return predicate;
}

StructuredScript::INode::Ptr StructuredScript::Parser::IterationParser::parseValue_(INode::Ptr predicate, ICharacterWell &well,
	IScanner &scanner, IParser &parser, IExceptionManager *exception){
	INode::Ptr value;
	if (!scanner.open(well, '{', '}')){//Line
		value = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
			return (next.value() != ";");
		});

		if (!Query::Node::isBlock(value))//Ignore ';'
			scanner.next(well);
	}
	else//Block
		value = parseBlock_(predicate, well, scanner, parser, exception);

	return Query::ExceptionManager::has(exception) ? nullptr : value;
}

StructuredScript::INode::Ptr StructuredScript::Parser::IterationParser::parseBlock_(INode::Ptr predicate, ICharacterWell &well,
	IScanner &scanner, IParser &parser, IExceptionManager *exception){
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

StructuredScript::Scanner::Plugins::SignedNumber StructuredScript::Parser::IterationParser::signedNumber_;
