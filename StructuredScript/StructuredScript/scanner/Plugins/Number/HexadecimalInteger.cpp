#include "HexadecimalInteger.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::HexadecimalInteger::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	well.step(2);//Skip '0x'
	well.fork();

	auto token = numberPlugin_->get(well, [filter](char next) -> unsigned short{
		if (next == '0')
			return IScannerPlugin::INCLUDE;

		if (!::isalpha(next))
			return IScannerPlugin::NONE;

		next = ::tolower(next);
		return ((next >= 'a' && next <= 'f') || (filter != nullptr && filter(next) == IScannerPlugin::INCLUDE)) ? IScannerPlugin::INCLUDE : IScannerPlugin::NONE;
	});

	well.merge();
	if (token.getType() != TokenType::TOKEN_TYPE_DECIMAL_INTEGER)
		return Token(TokenType::TOKEN_TYPE_ERROR, "0x" + token.getValue());

	return Token(TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER, token.getValue(), "0x");
}

bool StructuredScript::Scanner::Plugins::HexadecimalInteger::matches(const ICharacterWell &well) const{
	return (well.peek(2) == "0x");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::HexadecimalInteger::type() const{
	return TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER;
}
