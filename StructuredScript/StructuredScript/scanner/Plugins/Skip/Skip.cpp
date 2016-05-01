#include "Skip.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::Skip::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto token = blank_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	token = singleLineComment_.get(well, filter);
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return token;

	return multiLineComment_.get(well, filter);
}

bool StructuredScript::Scanner::Plugins::Skip::matches(const ICharacterWell &well) const{
	return (blank_.matches(well) || singleLineComment_.matches(well) || multiLineComment_.matches(well));
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::Skip::type() const{
	return TokenType::TOKEN_TYPE_BLANK;
}
