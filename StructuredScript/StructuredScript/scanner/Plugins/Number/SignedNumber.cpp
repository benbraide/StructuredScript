#include "SignedNumber.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::SignedNumber::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto sign = well.peek();

	well.step(1);//Skip '+' | '-'
	well.fork();

	auto blank = skip_(well);
	if (blank.getType() == TokenType::TOKEN_TYPE_ERROR){
		well.merge();
		return Token(TokenType::TOKEN_TYPE_ERROR, sign + blank.getValue());
	}

	auto token = numberPlugin_->get(well, filter);

	well.merge();
	if (token.getType() != TokenType::TOKEN_TYPE_NONE)
		return Token(token.getType(), sign + token.getValue());

	return Token(TokenType::TOKEN_TYPE_SYMBOL, std::string(1, sign));
}

bool StructuredScript::Scanner::Plugins::SignedNumber::matches(const ICharacterWell &well) const{
	auto next = well.peek();
	return (next == '+' || next == '-');
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::SignedNumber::type() const{
	return TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::SignedNumber::skip_(ICharacterWell &well) const{
	auto blank = skipPlugin_->get(well);
	if (blank.getType() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	while (blank.getType() != TokenType::TOKEN_TYPE_NONE){
		well.merge();
		well.fork();

		blank = skipPlugin_->get(well);
		if (blank.getType() == TokenType::TOKEN_TYPE_ERROR)
			return Token(TokenType::TOKEN_TYPE_ERROR, well.get());
	}

	return Token(TokenType::TOKEN_TYPE_NONE, "");
}
