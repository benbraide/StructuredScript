#include "Parser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::Parser::parse(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception,
	bool single /*= false*/){
	if (single)//Single line expression
		scanner.fork(';');

	auto node = expression_(nullptr, well, scanner, exception);
	if (single){
		scanner.close(well, true);
		return node;
	}

	if (Query::ExceptionManager::has(exception))
		return node;

	while (true){
		auto right = expression_(nullptr, well, scanner, exception);
		if (Query::ExceptionManager::has(exception) || Query::Node::isEmpty(right.get()))
			return node;

		node = std::make_shared<Nodes::BlockPairNode>(node, right);
	}

	return node;
}

StructuredScript::INode::Ptr StructuredScript::Parser::Parser::term_(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception){
	auto next = scanner.next(well, { &signedNumber_ });
	if (next.isError())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Error in token!"));

	auto type = next.type();
	if (type == Scanner::TokenType::TOKEN_TYPE_NONE)
		return std::make_shared<Nodes::EmptyNode>();

	if (Scanner::tokenIsLiteralType(type))
		return std::make_shared<Nodes::LiteralNode>(next);

	if (type == Scanner::Plugins::TypenameTokenType::type)
		return std::make_shared<Nodes::PrimitiveTypeIdentifierNode>(next.prefix(), next.value());

	if (type == Scanner::TokenType::TOKEN_TYPE_IDENTIFIER){
		//Check plugins...

		return std::make_shared<Nodes::IdentifierNode>(next.value());
	}

	OperatorInfo::MatchedListType list;
	operatorInfo.find(next.value(), OperatorType(OperatorType::LEFT_UNARY), list);
	if (list.empty())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Unrecognized symbol!"));

	auto info = list[OperatorType(OperatorType::LEFT_UNARY)];
	auto operand = expression_(nullptr, well, scanner, exception, info.precedence);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (Query::Node::isEmpty(operand.get()))
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Missing operand!"));

	return std::make_shared<Nodes::UnaryOperatorNode>(true, next.value(), operand);
}

StructuredScript::INode::Ptr StructuredScript::Parser::Parser::expression_(INode::Ptr node, ICharacterWell &well, IScanner &scanner,
	IExceptionManager *exception, short precedence /*= -1*/){
	if (node == nullptr){//Get term
		node = term_(well, scanner, exception);
		if (Query::ExceptionManager::has(exception) || Query::Node::isEmpty(node.get()))
			return node;

		if (Query::Node::isBlock(node.get()))
			return node;
	}

	auto next = scanner.next(well);
	if (next.isError())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Error in token!"));

	auto type = next.type();
	if (type == Scanner::TokenType::TOKEN_TYPE_NONE)
		return node;

	OperatorInfo::MatchedListType list;
	operatorInfo.find(next.value(), OperatorType(OperatorType::BINARY | OperatorType::RIGHT_UNARY), list);
	if (list.empty())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Unrecognized symbol!"));

	OperatorInfo::MatchedListType::iterator info;
	if (scanner.hasMore(well)){//Binary | RightUnary
		info = list.find(OperatorType(OperatorType::BINARY));
		if (info == list.end())
			info = list.find(OperatorType(OperatorType::RIGHT_UNARY));
	}
	else//RightUnary
		info = list.find(OperatorType(OperatorType::RIGHT_UNARY));

	if (info == list.end())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Bad operator!"));

	if (info->second.precedence < precedence || (info->second.precedence == precedence && info->second.isLeftAssociative)){//Don't stack
		scanner.save(next);
		return node;
	}

	if (info->first.isBinary()){
		auto right = expression_(nullptr, well, scanner, exception, info->second.precedence);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		node = std::make_shared<Nodes::BinaryOperatorNode>(next.value(), node, right);
	}
	else//RightUnary
		node = std::make_shared<Nodes::UnaryOperatorNode>(false, next.value(), node);

	return expression_(node, well, scanner, exception, precedence);
}

StructuredScript::OperatorInfo StructuredScript::Parser::Parser::operatorInfo;
