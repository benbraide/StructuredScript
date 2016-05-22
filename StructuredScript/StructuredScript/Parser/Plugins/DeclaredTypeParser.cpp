#include "DeclaredTypeParser.h"

StructuredScript::INode::Ptr StructuredScript::Parser::DeclaredTypeParser::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
	auto idCount = 0;
	auto value = parser.expression(nullptr, well, scanner, exception, -1, [&idCount](const Scanner::Token &next) -> bool{
		switch (next.type()){
		case Scanner::TokenType::TOKEN_TYPE_IDENTIFIER:
		case Scanner::Plugins::TypenameTokenType::type://Stop at the first identifier token
			return (idCount++ == 0);
		case Scanner::TokenType::TOKEN_TYPE_SYMBOL:
			return (next.value() == "<" || next.value() == "[" || next.value() == "::");
		default:
			break;
		}

		return false;
	});

	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (!Query::Node::isIdentifier(value) || Query::Node::isOperatorIdentifier(value)){//Type identifier required
		return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
			"'" + state_.str() + " " + value->str() + "': Expected type after state modifier!"));
	}

	auto modifiedType = dynamic_cast<IModifiedTypeIdentifierNode *>(value.get());
	if (modifiedType != nullptr){//Add states
		if ((modifiedType->states() & state_.states()) != 0u){//Bad declaration
			return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString(
				"'" + state_.str() + " " + value->str() + "': Bad expression!"));
		}

		modifiedType->states(modifiedType->states() | state_.states());//Add state to declaration states
		return value;
	}

	return std::make_shared<Nodes::ModifiedTypenameIdentifierNode>(value, state_);//Create declared type node
}

const StructuredScript::Storage::MemoryState &StructuredScript::Parser::DeclaredTypeParser::state() const{
	return state_;
}

unsigned short StructuredScript::Parser::DeclaredTypeParser::translate(const std::string &state){
	if (state == "const")
		return Storage::MemoryState::STATE_CONSTANT;

	if (state == "final")
		return Storage::MemoryState::STATE_FINAL;

	if (state == "static")
		return Storage::MemoryState::STATE_STATIC;

	if (state == "private")
		return Storage::MemoryState::STATE_PRIVATE;

	if (state == "protected")
		return Storage::MemoryState::STATE_PROTECTED;

	if (state == "public")
		return Storage::MemoryState::STATE_PUBLIC;

	if (state == "ref")
		return Storage::MemoryState::STATE_REFERENCE;

	if (state == "val")
		return Storage::MemoryState::STATE_RVALUE;

	return Storage::MemoryState::STATE_NONE;
}
