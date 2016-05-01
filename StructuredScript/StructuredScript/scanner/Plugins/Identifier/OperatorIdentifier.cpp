#include "OperatorIdentifier.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto token = get_(well, BinaryOperatorTokenType::type, "operator", filter);
	if (token.getType() != TokenType::TOKEN_TYPE_IDENTIFIER)
		return token;

	TokenType type;
	auto value = token.getValue();
	if (value == "left")
		type = LeftUnaryOperatorTokenType::type;
	else if (value == "right")
		type = RightUnaryOperatorTokenType::type;
	else
		return Token(BinaryOperatorTokenType::type, value, "operator ");

	return get_(well, type, "operator " + value, filter);
}

bool StructuredScript::Scanner::Plugins::OperatorIdentifier::matches(const ICharacterWell &well) const{
	return (well.get() == "operator");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::OperatorIdentifier::type() const{
	return TokenType::TOKEN_TYPE_IDENTIFIER;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::get_(ICharacterWell &well,
	TokenType type, const std::string &prefix, FilterType filter) const{
	well.fork();
	
	auto blank = skip_(well);
	if (blank.getType() == TokenType::TOKEN_TYPE_ERROR){
		well.merge();
		return blank;
	}

	auto token = identifierPlugin_->get(well, filter);
	well.merge();

	if (token.getType() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	if (token.getType() == TokenType::TOKEN_TYPE_NONE)//Try symbol
		return getSymbol_(well, type, prefix, filter);

	return token;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::getSymbol_(ICharacterWell &well,
	TokenType type, const std::string &prefix, FilterType filter) const{
	well.fork();

	auto blank = skip_(well);
	if (blank.getType() == TokenType::TOKEN_TYPE_ERROR)
		return blank;

	auto token = symbolPlugin_->get(well);
	well.merge();

	if (token.getType() != TokenType::TOKEN_TYPE_SYMBOL)//Missing operator symbol
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	return Token(type, token.getValue(), prefix + " ");
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::OperatorIdentifier::skip_(ICharacterWell &well) const{
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
