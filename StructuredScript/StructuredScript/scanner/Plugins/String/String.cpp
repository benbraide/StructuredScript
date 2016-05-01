#include "String.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::String::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto token = doublyQuotedString_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	token = doublyQuotedRawString_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	token = singlyQuotedString_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	token = singlyQuotedRawString_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	token = backQuotedString_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	return backQuotedRawString_.get(well, filter);
}

bool StructuredScript::Scanner::Plugins::String::matches(const ICharacterWell &well) const{
	return (doublyQuotedString_.matches(well) || doublyQuotedRawString_.matches(well) || singlyQuotedString_.matches(well) ||
		singlyQuotedRawString_.matches(well) || backQuotedString_.matches(well) || backQuotedRawString_.matches(well));
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::String::type() const{
	return TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING;
}
