#include "OctalInteger.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OctalInteger::get(ICharacterWell &well, FilterType filter){
	if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	well.step(1);//Skip '0'
	well.fork();

	auto token = decimalInteger_.get(well, [filter](char next) -> unsigned short{
		if (filter != nullptr){
			auto state = filter(next);
			if (state != IScannerPlugin::NONE)
				return state;
		}

		if (next == '0')
			return IScannerPlugin::INCLUDE;

		return (::isdigit(next) && (next < '0' || next > '7')) ? IScannerPlugin::FAIL : IScannerPlugin::NONE;
	});

	well.merge();
	if (token.type() == TokenType::TOKEN_TYPE_NONE)
		return Token(TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "0");

	if (token.type() != TokenType::TOKEN_TYPE_DECIMAL_INTEGER)
		return Token(TokenType::TOKEN_TYPE_ERROR, "0" + token.value());

	return Token(TokenType::TOKEN_TYPE_OCTAL_INTEGER, token.value(), "0");
}

bool StructuredScript::Scanner::Plugins::OctalInteger::matches(ICharacterWell &well){
	auto peek = well.peek(2);
	if (peek.empty() || peek[0] != '0')
		return false;

	return (peek.size() == 1u || (peek[1] != 'x' && peek[1] != 'b'));
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::OctalInteger::type() const{
	return TokenType::TOKEN_TYPE_OCTAL_INTEGER;
}
