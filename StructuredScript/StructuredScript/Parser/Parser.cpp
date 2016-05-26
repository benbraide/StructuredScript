#include "Parser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::Parser::parse(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception,
	Validator validator/* = nullptr*/, bool single /*= false*/){
	if (single)//Single line | block expression
		scanner.fork(';');

	auto node = expression(nullptr, well, scanner, exception, -1, validator);
	if (single){
		scanner.close(well, true);
		return node;
	}

	if (Query::ExceptionManager::has(exception))
		return node;

	while (true){
		auto right = expression(nullptr, well, scanner, exception, -1, validator);
		if (Query::ExceptionManager::has(exception) || Query::Node::isEmpty(right))
			return node;

		if (scanner.hasMore(well) && !Query::Node::isBlock(node)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + node->str() + " " + scanner.next(well).value() + "...': Bad expression!"));
		}

		node = std::make_shared<Nodes::BlockPairNode>(node, right);
	}

	return node;
}

StructuredScript::INode::Ptr StructuredScript::Parser::Parser::term(ICharacterWell &well, IScanner &scanner, IExceptionManager *exception,
	Validator validator/* = nullptr*/){
	auto next = scanner.next(well, { &signedNumber_ });
	if (next.isError())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Error in token!"));

	auto type = next.type();
	if (type == Scanner::TokenType::TOKEN_TYPE_NONE)
		return std::make_shared<Nodes::EmptyNode>();

	if (validator != nullptr && !validator(next)){//Denied
		scanner.save(next);
		return std::make_shared<Nodes::EmptyNode>();
	}

	if (Scanner::tokenIsLiteralType(type))
		return std::make_shared<Nodes::LiteralNode>(next);

	auto value = next.value();
	if (type == Scanner::Plugins::TypenameTokenType::type)
		return std::make_shared<Nodes::PrimitiveTypeIdentifierNode>(value);

	if (value == "@"){
		auto node = AtSymbolParser(validator).parse(well, scanner, *this, exception);
		if (node != nullptr || Query::ExceptionManager::has(exception))
			return node;
	}

	if (value[0] == '(' || value[0] == '[' || value[0] == '{'){//Group
		scanner.save(next);//Save symbol
		return GroupParser(nullptr, operatorInfo, -1).parse(well, scanner, *this, exception);
	}

	OperatorInfo::MatchedListType list;
	operatorInfo.find(value, OperatorType(OperatorType::LEFT_UNARY), list);
	if (list.empty()){
		if (type == Scanner::TokenType::TOKEN_TYPE_IDENTIFIER){
			auto plugin = plugins_.find(value);
			if (plugin != plugins_.end())//Use plugin
				return plugin->second->parse(well, scanner, *this, exception);

			if (value == "break")
				return std::make_shared<Nodes::BreakNode>();

			if (value == "continue")
				return std::make_shared<Nodes::ContinueNode>();

			DeclaredTypeParser declaredTypeParser(value);//Check if id is a modifier
			if (declaredTypeParser.state().states() != Storage::MemoryState::STATE_NONE)
				return declaredTypeParser.parse(well, scanner, *this, exception);

			return std::make_shared<Nodes::IdentifierNode>(value);
		}

		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Unrecognized symbol!"));
	}

	auto info = list[OperatorType(OperatorType::LEFT_UNARY)];
	auto operand = expression(nullptr, well, scanner, exception, info.precedence, validator);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (value == "throw")
		return std::make_shared<Nodes::ThrowNode>(operand);

	if (value == "new")
		return std::make_shared<Nodes::NewNode>(operand);

	if (value == "typeof")
		return std::make_shared<Nodes::TypeOfNode>(operand);

	if (value == "sizeof")
		return std::make_shared<Nodes::SizeOfNode>(operand);

	if (Query::Node::isEmpty(operand))
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Missing operand!"));

	return std::make_shared<Nodes::UnaryOperatorNode>(true, value, operand);
}

StructuredScript::INode::Ptr StructuredScript::Parser::Parser::expression(INode::Ptr node, ICharacterWell &well, IScanner &scanner,
	IExceptionManager *exception, short precedence /*= -1*/, Validator validator/* = nullptr*/){
	if (node == nullptr){//Get term
		node = term(well, scanner, exception, validator);
		if (Query::ExceptionManager::has(exception) || Query::Node::isEmpty(node))
			return node;
	}

	if (Query::Node::isBlock(node))
		return node;

	auto next = scanner.next(well);
	if (next.isError())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Error in token!"));

	auto type = next.type();
	if (type == Scanner::TokenType::TOKEN_TYPE_NONE)
		return node;

	if (validator != nullptr && !validator(next)){//Denied
		scanner.save(next);
		return node;
	}

	auto value = next.value();
	if (value == "=" && (Query::Node::isDeclaration(node) || Query::Node::isTypeIdentifier(node))){
		if (Query::Node::isInitialization(node)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + node->str() + " " + next.str() + "': Bad expression!"));
		}

		if (Query::Node::isTypeIdentifier(node))//Unnamed declaration
			node = std::make_shared<Nodes::DeclarationNode>(node, nullptr);

		node = InitializationParser(node).parse(well, scanner, *this, exception);
		if (Query::ExceptionManager::has(exception))
			return node;

		return expression(node, well, scanner, exception, precedence, validator);
	}

	if (value == "," && Query::Node::isDeclaration(node)){//Multiple declarations
		node = DependentDeclarationParser(node).parse(well, scanner, *this, exception);
		if (Query::ExceptionManager::has(exception))
			return node;

		return expression(node, well, scanner, exception, precedence, validator);
	}

	if (value == "<" && Query::Node::isTypeIdentifier(node)){//Templated typename
		scanner.fork('>');
		auto content = expression(nullptr, well, scanner, exception, -1, validator);

		if (!scanner.close(well)){
			if (!Query::ExceptionManager::has(exception)){
				return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
					"'" + node->str() + "<" + content->str() + "...': Bad expression!"));
			}

			return nullptr;
		}

		if (Query::ExceptionManager::has(exception))
			return nullptr;

		node = std::make_shared<Nodes::TemplatedTypenameIdentifierNode>(node, content);
		return expression(node, well, scanner, exception, precedence, validator);
	}

	if (value == "..." && Query::Node::isIdentifier(node) && !Query::Node::isOperatorIdentifier(node)){//Expanded type | identifier
		if (Query::Node::isTypeIdentifier(node))
			node = std::make_shared<Nodes::ExpandedTypenameIdentifierNode>(node);
		else
			node = std::make_shared<Nodes::UnaryOperatorNode>(false, "...", node);
		
		return expression(node, well, scanner, exception, precedence, validator);
	}

	if (value[0] == '(' || value[0] == '[' || value[0] == '{'){//Group
		scanner.save(next);//Save symbol
		auto value = GroupParser(node, operatorInfo, precedence).parse(well, scanner, *this, exception);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (value == node)//Operator stacking was rejected
			return node;

		return expression(value, well, scanner, exception, precedence, validator);
	}

	OperatorInfo::MatchedListType list;
	operatorInfo.find(value, OperatorType(OperatorType::BINARY | OperatorType::RIGHT_UNARY), list);

	if (list.empty()){//Check declaration
		if (type == Scanner::TokenType::TOKEN_TYPE_IDENTIFIER && (Query::Node::isClass(node) || (Query::Node::isIdentifier(node) &&
			!Query::Node::isOperatorIdentifier(node)))){//Declaration

			scanner.save(next);
			node = DeclarationParser(node).parse(well, scanner, *this, exception);
			if (Query::ExceptionManager::has(exception))
				return node;

			return expression(node, well, scanner, exception, precedence, validator);
		}

		if (type == Scanner::TokenType::TOKEN_TYPE_SYMBOL)
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Unrecognized symbol!"));

		scanner.save(next);
		return node;
	}

	OperatorInfo::MatchedListType::iterator info;
	if (scanner.hasMore(well)){//Binary | Right unary
		info = list.find(OperatorType(OperatorType::BINARY));
		if (info == list.end())
			info = list.find(OperatorType(OperatorType::RIGHT_UNARY));
	}
	else//Right unary
		info = list.find(OperatorType(OperatorType::RIGHT_UNARY));

	if (info == list.end())
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + next.str() + "': Bad operator!"));

	if (info->second.precedence < precedence || (info->second.precedence == precedence && info->second.isLeftAssociative)){//Don't stack
		scanner.save(next);
		return node;
	}

	if (info->first.isBinary()){
		if (value == "?"){//Conditional operator
			node = ConditionalParser(node, info->second.precedence).parse(well, scanner, *this, exception);
			if (Query::ExceptionManager::has(exception))
				return node;

			return expression(node, well, scanner, exception, precedence, validator);
		}

		auto right = expression(nullptr, well, scanner, exception, info->second.precedence, validator);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (Query::Node::isEmpty(node)){
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + node->str() + " " + next.str() + "': Missing right operand!"));
		}

		node = std::make_shared<Nodes::BinaryOperatorNode>(value, node, right);
	}
	else//RightUnary
		node = std::make_shared<Nodes::UnaryOperatorNode>(false, value, node);

	return expression(node, well, scanner, exception, precedence, validator);
}

void StructuredScript::Parser::Parser::init(){
	plugins_["typename"] = std::make_shared<TypenameParser>();
	plugins_["operator"] = std::make_shared<OperatorParser>();
	plugins_["using"] = std::make_shared<UseParser>();

	plugins_["namespace"] = std::make_shared<NamespaceParser>();
	plugins_["enum"] = std::make_shared<EnumParser>();
	plugins_["class"] = std::make_shared<ClassParser>();

	plugins_["if"] = std::make_shared<SelectionParser>("if");
	plugins_["unless"] = std::make_shared<SelectionParser>("unless");
	plugins_["else"] = std::make_shared<SelectionParser>("else");

	plugins_["do"] = std::make_shared<IterationParser>("do");
	plugins_["while"] = std::make_shared<IterationParser>("while");
	plugins_["for"] = std::make_shared<IterationParser>("for");

	plugins_["try"] = std::make_shared<ExceptionParser>("try");
	plugins_["catch"] = std::make_shared<ExceptionParser>("catch");
	plugins_["finally"] = std::make_shared<ExceptionParser>("finally");

	plugins_["return"] = std::make_shared< SourceParser<Nodes::ReturnNode, true, false> >("return");
	plugins_["echo"] = std::make_shared< SourceParser<Nodes::EchoNode, false, false> >("echo");

	operatorInfo.init();
}

StructuredScript::OperatorInfo StructuredScript::Parser::Parser::operatorInfo;

StructuredScript::Scanner::Plugins::SignedNumber StructuredScript::Parser::Parser::signedNumber_;

StructuredScript::Parser::Parser::PluginListType StructuredScript::Parser::Parser::plugins_;
