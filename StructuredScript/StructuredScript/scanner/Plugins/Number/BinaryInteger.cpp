#include "BinaryInteger.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::BinaryInteger::get(ICharacterWell &well, FilterType filter){
	if (matches(well))
		well.step(2);//Skip '0b'
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

		return (::isdigit(next) && (next < '0' || next > '1')) ? IScannerPlugin::FAIL : IScannerPlugin::NONE;
	});

	well.merge();
	if (token.type() != TokenType::TOKEN_TYPE_DECIMAL_INTEGER)
		return Token(TokenType::TOKEN_TYPE_ERROR, "0b" + token.value());

	return Token(TokenType::TOKEN_TYPE_BINARY_INTEGER, token.value(), "0b");
}

bool StructuredScript::Scanner::Plugins::BinaryInteger::matches(ICharacterWell &well){
	return (well.peek(2) == "0b");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::BinaryInteger::type() const{
	return TokenType::TOKEN_TYPE_BINARY_INTEGER;
}
