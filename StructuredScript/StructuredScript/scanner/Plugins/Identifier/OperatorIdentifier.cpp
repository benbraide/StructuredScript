#include "OperatorIdentifier.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::get(ICharacterWell &well, FilterType filter){
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto token = get_(well, OperatorTokenType::type, "operator", filter);
	if (token.type() != TokenType::TOKEN_TYPE_IDENTIFIER)
		return token;

	return Token(OperatorTokenType::type, token.value(), "operator ");
}

bool StructuredScript::Scanner::Plugins::OperatorIdentifier::matches(ICharacterWell &well){
	return (well.get() == "operator");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::OperatorIdentifier::type() const{
	return TokenType::TOKEN_TYPE_IDENTIFIER;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::get_(ICharacterWell &well,
	TokenType type, const std::string &prefix, FilterType filter){
	well.fork();
	
	auto blank = skip_(well);
	if (blank.type() == TokenType::TOKEN_TYPE_ERROR){
		well.merge();
		return blank;
	}

	auto token = identifierPlugin_.get(well, filter);
	well.merge();

	if (token.type() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	if (token.type() == TokenType::TOKEN_TYPE_NONE)//Try symbol
		return getSymbol_(well, type, prefix, filter);

	return token;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::getSymbol_(ICharacterWell &well,
	TokenType type, const std::string &prefix, FilterType filter){
	well.fork();

	auto blank = skip_(well);
	if (blank.type() == TokenType::TOKEN_TYPE_ERROR)
		return blank;

	auto token = symbolPlugin_.get(well);
	well.merge();

	if (token.type() != TokenType::TOKEN_TYPE_SYMBOL)//Missing operator symbol
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	return Token(type, token.value(), prefix + " ");
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::skip_(ICharacterWell &well){
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
