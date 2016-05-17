#include "SignedNumber.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::SignedNumber::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto sign = well.peek();

	well.step(1);//Skip '+' | '-'
	well.fork();

	auto blank = skip_(well);
	if (blank.type() == TokenType::TOKEN_TYPE_ERROR){
		well.merge();
		return Token(TokenType::TOKEN_TYPE_ERROR, sign + blank.value());
	}

	auto token = numberPlugin_.get(well, filter);

	well.merge();
	if (token.type() != TokenType::TOKEN_TYPE_NONE)
		return Token(token.type(), sign + token.value(), token.prefix(), token.suffix(), false, 1);

	return Token(TokenType::TOKEN_TYPE_SYMBOL, std::string(1, sign));
}

bool StructuredScript::Scanner::Plugins::SignedNumber::matches(const ICharacterWell &well) const{
	auto next = well.peek(2);
	if (next.empty() || (next[0] != '+' && next[0] != '-'))
		return false;

	if (next.size() == 1u)
		return true;

	return (::ispunct(next[1]) == 0);
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::SignedNumber::type() const{
	return TokenType::TOKEN_TYPE_REAL_NUMBER;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::SignedNumber::skip_(ICharacterWell &well) const{
	auto blank = skipPlugin_.get(well);
	if (blank.type() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	while (blank.type() != TokenType::TOKEN_TYPE_NONE){
		well.merge();
		well.fork();

		blank = skipPlugin_.get(well);
		if (blank.type() == TokenType::TOKEN_TYPE_ERROR)
			return Token(TokenType::TOKEN_TYPE_ERROR, well.get());
	}

	return Token(TokenType::TOKEN_TYPE_NONE, "");
}
