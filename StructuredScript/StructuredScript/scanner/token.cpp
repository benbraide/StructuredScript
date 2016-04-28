#include "token.h"

bool StructuredScript::Scanner::Token::operator ==(const Token &right) const{
	return (type_ == right.type_ && value_ == right.value_);
}

bool StructuredScript::Scanner::Token::operator !=(const Token &right) const{
	return (type_ != right.type_ || value_ != right.value_);
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Token::getType() const{
	return type_;
}

std::string StructuredScript::Scanner::Token::getValue() const{
	return value_;
}

std::string StructuredScript::Scanner::Token::str() const{
	return (prefix_ + value_ + postfix_);
}

StructuredScript::Scanner::TokenGroup StructuredScript::Scanner::Token::getGroup() const{
	if (tokenIsNumberType(type_))
		return TokenGroup::TOKEN_GROUP_NUMBER;

	if (tokenIsStringType(type_))
		return TokenGroup::TOKEN_GROUP_STRING;

	return TokenGroup::TOKEN_GROUP_GROUP;
}

bool StructuredScript::Scanner::Token::isGroup(TokenGroup group) const{
	return (getGroup() == group);
}

bool StructuredScript::Scanner::Token::isError() const{
	return (type_ == TokenType::TOKEN_TYPE_ERROR);
}

bool StructuredScript::Scanner::Token::isValid() const{
	return (type_ != TokenType::TOKEN_TYPE_ERROR && type_ != TokenType::TOKEN_TYPE_NONE);
}

bool StructuredScript::Scanner::tokenIsNumberType(TokenType type){
	return  (
				type == TokenType::TOKEN_TYPE_DECIMAL_INTEGER		||
				type == TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER	||
				type == TokenType::TOKEN_TYPE_OCTAL_INTEGER			||
				type == TokenType::TOKEN_TYPE_BINARY_INTEGER		||
				type == TokenType::TOKEN_TYPE_REAL_NUMBER				||
				type == TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER
			);
}

bool StructuredScript::Scanner::tokenIsStringType(TokenType type){
	return  (
				type == TokenType::TOKEN_TYPE_DOUBLE_QUOTED_STRING	||
				type == TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING	||
				type == TokenType::TOKEN_TYPE_BACK_QUOTED_STRING
			);
}

bool StructuredScript::Scanner::tokenIsGroupType(TokenType type){
	return  (
				type == TokenType::TOKEN_TYPE_GROUP					||
				type == TokenType::TOKEN_TYPE_INDEX					||
				type == TokenType::TOKEN_TYPE_BLOCK					||
				type == TokenType::TOKEN_TYPE_ANGLE
			);
}
