#include "SingleLineComment.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::SingleLineComment::get(ICharacterWell &well, FilterType filter){
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	well.step(2);//Skip '//'
	well.fork();

	if (!well.stepTo('\n'))
		well.stepToEnd();

	auto value = well.get();
	well.merge();

	return Token(TokenType::TOKEN_TYPE_SINGLE_LINE_COMMENT, value, "//");
}

bool StructuredScript::Scanner::Plugins::SingleLineComment::matches(ICharacterWell &well){
	return (well.peek(2) == "//");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::SingleLineComment::type() const{
	return TokenType::TOKEN_TYPE_SINGLE_LINE_COMMENT;
}
