#include "HexadecimalInteger.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::HexadecimalInteger::get(ICharacterWell &well, FilterType filter) const{
	if (matches(well))
		well.step(2);//Skip '0x'
	else if (filter != nullptr && filter(well.peek()) == IScannerPlugin::INCLUDE)
		well.step(1);//Skip
	else
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	well.fork();
	auto token = decimalInteger_.get(well, [filter](char next) -> unsigned short{
		if (filter != nullptr){
			auto state = filter(next);
			if (state != IScannerPlugin::NONE)
				return state;
		}

		if (next == '0')
			return IScannerPlugin::INCLUDE;

		if (!::isalpha(next))
			return IScannerPlugin::NONE;

		next = ::tolower(next);
		return ((next >= 'a' && next <= 'f')) ? IScannerPlugin::INCLUDE : IScannerPlugin::NONE;
	});

	well.merge();
	if (token.type() != TokenType::TOKEN_TYPE_DECIMAL_INTEGER)
		return Token(TokenType::TOKEN_TYPE_ERROR, "0x" + token.value());

	return Token(TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER, token.value(), "0x");
}

bool StructuredScript::Scanner::Plugins::HexadecimalInteger::matches(const ICharacterWell &well) const{
	return (well.peek(2) == "0x");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::HexadecimalInteger::type() const{
	return TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER;
}
