#include "BinaryInteger.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::BinaryInteger::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	well.step(2);//Skip '0b'
	well.fork();

	auto token = numberPlugin_->get(well, [filter](char next) -> unsigned short{
		if (next == '0')
			return IScannerPlugin::INCLUDE;

		return (::isdigit(next) && (next < '0' || next > '1')) ? IScannerPlugin::FAIL : IScannerPlugin::NONE;
	});

	well.merge();
	if (token.getType() != TokenType::TOKEN_TYPE_DECIMAL_INTEGER)
		return Token(TokenType::TOKEN_TYPE_ERROR, "0b" + token.getValue());

	return Token(TokenType::TOKEN_TYPE_BINARY_INTEGER, token.getValue(), "0b");
}

bool StructuredScript::Scanner::Plugins::BinaryInteger::matches(const ICharacterWell &well) const{
	return (well.peek(2) == "0b");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::BinaryInteger::type() const{
	return TokenType::TOKEN_TYPE_BINARY_INTEGER;
}
