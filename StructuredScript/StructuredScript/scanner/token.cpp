#include "token.h"

bool StructuredScript::Scanner::Token::operator ==(const Token &right) const{
	return (type_ == right.type_ && value_ == right.value_);
}

bool StructuredScript::Scanner::Token::operator !=(const Token &right) const{
	return (type_ != right.type_ || value_ != right.value_);
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Token::type() const{
	return type_;
}

std::string StructuredScript::Scanner::Token::value() const{
	return value_;
}

std::string StructuredScript::Scanner::Token::str() const{
	if (skipValue_)
		return (prefix_ + suffix_);

	auto value = value_;
	value.insert(prefixOffset_, prefix_);

	return (value + suffix_);
}

std::string StructuredScript::Scanner::Token::prefix() const{
	return prefix_;
}

std::string StructuredScript::Scanner::Token::suffix() const{
	return suffix_;
}

bool StructuredScript::Scanner::Token::skipValue() const{
	return skipValue_;
}

unsigned int StructuredScript::Scanner::Token::prefixOffset() const{
	return prefixOffset_;
}

StructuredScript::Scanner::TokenGroup StructuredScript::Scanner::Token::group() const{
	if (tokenIsNumberType(type_))
		return TokenGroup::TOKEN_GROUP_NUMBER;

	if (tokenIsStringType(type_))
		return TokenGroup::TOKEN_GROUP_STRING;

	return TokenGroup::TOKEN_GROUP_GROUP;
}

bool StructuredScript::Scanner::Token::isGroup(TokenGroup group) const{
	return (this->group() == group);
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
				type == TokenType::TOKEN_TYPE_RADIX_INTEGER			||
				type == TokenType::TOKEN_TYPE_REAL_NUMBER			||
				type == TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER
			);
}

bool StructuredScript::Scanner::tokenIsIntegerType(TokenType type){
	return  (
				type == TokenType::TOKEN_TYPE_DECIMAL_INTEGER		||
				type == TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER	||
				type == TokenType::TOKEN_TYPE_OCTAL_INTEGER			||
				type == TokenType::TOKEN_TYPE_BINARY_INTEGER		||
				type == TokenType::TOKEN_TYPE_RADIX_INTEGER
			);
}

bool StructuredScript::Scanner::tokenIsRealType(TokenType type){
	return  (
				type == TokenType::TOKEN_TYPE_REAL_NUMBER			||
				type == TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER
			);
}

bool StructuredScript::Scanner::tokenIsStringType(TokenType type){
	return  (
				type == TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING		||
				type == TokenType::TOKEN_TYPE_DOUBLY_QUOTED_RAW_STRING	||
				type == TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING		||
				type == TokenType::TOKEN_TYPE_SINGLY_QUOTED_RAW_STRING	||
				type == TokenType::TOKEN_TYPE_BACK_QUOTED_STRING		||
				type == TokenType::TOKEN_TYPE_BACK_QUOTED_RAW_STRING
			);
}

bool StructuredScript::Scanner::tokenIsRawStringType(TokenType type){
	return  (
				type == TokenType::TOKEN_TYPE_DOUBLY_QUOTED_RAW_STRING	||
				type == TokenType::TOKEN_TYPE_SINGLY_QUOTED_RAW_STRING	||
				type == TokenType::TOKEN_TYPE_BACK_QUOTED_RAW_STRING
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
