#include "SelectionParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::SelectionParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	if (name_ != "else"){// 'if' | 'unless'
		if (!scanner.open(well, '(', ')')){//Extract parameters
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + name_ + "...': Bad expression!"));
		}

		auto predicate = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
			return (next.value() != ";");
		});

		if (!scanner.close(well)){
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + name_ + "(" + predicate->str() + "...': Bad expression!"));
		}

		auto value = parseValue_(predicate, well, scanner, parser, exception);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (scanner.peek(well, { &signedNumber_ }).value() == "else"){
			scanner.next(well);//Ignore

			auto elseNode = SelectionParser("else", true).parse(well, scanner, parser, exception);
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			if (name_[0] == 'i')// else if
				return std::make_shared< Nodes::ControlExtension<Nodes::IfNode> >(elseNode, predicate, value);

			return std::make_shared< Nodes::ControlExtension<Nodes::UnlessNode> >(elseNode, predicate, value);
		}

		if (name_[0] == 'i')
			return std::make_shared<Nodes::IfNode>(predicate, value);

		return std::make_shared<Nodes::UnlessNode>(predicate, value);
	}

	if (!matched_){
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'else': Found without matching control block!"));
	}
	
	auto value = parseValue_(nullptr, well, scanner, parser, exception);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return std::make_shared<Nodes::ElseNode>(value);
}

StructuredScript::INode::Ptr StructuredScript::Parser::SelectionParser::parseValue_(INode::Ptr predicate, ICharacterWell &well,
	IScanner &scanner, IParser &parser, IExceptionManager *exception){
	INode::Ptr value;
	if (scanner.open(well, '{', '}')){//Block
		value = parser.parse(well, scanner, exception);
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
	}
	else{//Line
		value = parser.expression(nullptr, well, scanner, exception, -1, [](const Scanner::Token &next) -> bool{
			return (next.value() != ";");
		});

		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (!Query::Node::isBlock(value))//Ignore ';'
			scanner.next(well);
	}

	return value;
}

StructuredScript::Scanner::Plugins::SignedNumber StructuredScript::Parser::SelectionParser::signedNumber_;
