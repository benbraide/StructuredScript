#include "token.h"

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Token::getType() const{
	return type_;
}

std::string StructuredScript::Scanner::Token::getValue() const{
	return value_;
}

std::string StructuredScript::Scanner::Token::str() const{
	return (getTypeString_() + value_);
}

StructuredScript::Scanner::TokenGroup StructuredScript::Scanner::Token::getGroup() const{
	if (tokenIsNumberType(type_))
		return TokenGroup::TOKEN_GROUP_NUMBER;

	if (tokenIsStringType(type_))
		return TokenGroup::TOKEN_GROUP_STRING;

	if (tokenIsIdentifierType(type_))
		return TokenGroup::TOKEN_GROUP_IDENTIFIER;

	if (tokenIsOperatorType(type_))
		return TokenGroup::TOKEN_GROUP_OPERATOR;

	return TokenGroup::TOKEN_GROUP_GROUP;
}

bool StructuredScript::Scanner::Token::isGroup(TokenGroup group) const{
	return (getGroup() == group);
}

bool StructuredScript::Scanner::Token::isError() const{
	return (type_ == TokenType::TOKEN_TYPE_ERROR);
}

std::string StructuredScript::Scanner::Token::getTypeString_() const{
	return std::string();
}
