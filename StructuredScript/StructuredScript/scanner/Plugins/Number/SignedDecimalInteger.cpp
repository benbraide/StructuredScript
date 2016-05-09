#include "SignedDecimalInteger.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::SignedDecimalInteger::get(ICharacterWell &well, FilterType filter) const{
	if (decimalInteger_.matches(well) || (filter != nullptr && filter(well.peek()) == IScannerPlugin::INCLUDE))
		return decimalInteger_.get(well, filter);

	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto sign = well.peek();

	well.step(1);//Skip '+' | '-'
	well.fork();

	auto token = decimalInteger_.get(well, filter);

	well.merge();
	if (token.type() != TokenType::TOKEN_TYPE_NONE)
		return Token(token.type(), sign + token.value(), token.prefix(), token.suffix(), false, 1);

	return Token(TokenType::TOKEN_TYPE_SYMBOL, std::string(1, sign));
}

bool StructuredScript::Scanner::Plugins::SignedDecimalInteger::matches(const ICharacterWell &well) const{
	auto next = well.peek();
	return (next == '+' || next == '-');
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::SignedDecimalInteger::type() const{
	return TokenType::TOKEN_TYPE_DECIMAL_INTEGER;
}
