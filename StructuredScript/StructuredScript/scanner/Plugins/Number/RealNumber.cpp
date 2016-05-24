#include "RealNumber.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::RealNumber::get(ICharacterWell &well, FilterType filter){
	auto oct = octalInteger_.get(well, filter);
	auto type = oct.type();

	if (type != TokenType::TOKEN_TYPE_NONE && type != TokenType::TOKEN_TYPE_DECIMAL_INTEGER)
		return oct;

	auto dec = (type == TokenType::TOKEN_TYPE_NONE) ? decimalInteger_.get(well, filter) : oct;

	type = dec.type();
	if (type != TokenType::TOKEN_TYPE_NONE && type != TokenType::TOKEN_TYPE_DECIMAL_INTEGER)
		return dec;

	auto next = well.peek();
	if (next == '.' || next == 'e' || next == 'E'){
		if (next != '.' && type == TokenType::TOKEN_TYPE_NONE)//Identifier -- Ignore
			return dec;

		well.step(1);
		well.fork();

		auto right = (next == '.') ? decimalInteger_.get(well, filter) : signedDecimalInteger_.get(well, filter);
		
		well.merge();
		switch (right.type()){
		case TokenType::TOKEN_TYPE_NONE:
			if (next != '.')//Signed decimal integer required after 'e' | 'E'
				return Token(TokenType::TOKEN_TYPE_ERROR, dec.str() + next);

			well.step(-1);//Restore '.' -- Ignore trailing '.'
			return dec;
		case TokenType::TOKEN_TYPE_DECIMAL_INTEGER:
			if (next == '.')
				return Token(TokenType::TOKEN_TYPE_REAL_NUMBER, dec.value() + next + right.value());
			return Token(TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER, dec.value() + next + right.value());
		default:
			break;
		}

		return Token(TokenType::TOKEN_TYPE_ERROR, dec.str() + next + right.str());
	}

	return dec;
}

bool StructuredScript::Scanner::Plugins::RealNumber::matches(ICharacterWell &well){
	return (well.peek() == '.' || decimalInteger_.matches(well));
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::RealNumber::type() const{
	return TokenType::TOKEN_TYPE_REAL_NUMBER;
}
