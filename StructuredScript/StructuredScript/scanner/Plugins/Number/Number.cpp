#include "Number.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::Number::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto token = binaryInteger_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	token = hexadecimalInteger_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	token = octalInteger_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	return realNumber_.get(well, filter);
}

bool StructuredScript::Scanner::Plugins::Number::matches(const ICharacterWell &well) const{
	return (binaryInteger_.matches(well) || hexadecimalInteger_.matches(well) || octalInteger_.matches(well) || realNumber_.matches(well));
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::Number::type() const{
	return TokenType::TOKEN_TYPE_REAL_NUMBER;
}
