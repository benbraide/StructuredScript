#include "MultiLineComment.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::MultiLineComment::get(ICharacterWell &well, FilterType filter){
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	well.step(2);//Skip '/*'
	well.fork();
	
	auto next = well.next();
	if (next == '\0')//Missing closing '*/'
		return Token(TokenType::TOKEN_TYPE_ERROR, "/*" + well.get());

	auto hasErrors = false;
	auto filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);

	while (next != '*' || well.peek() != '/' || filterState != IScannerPlugin::NONE){
		if (!hasErrors && filterState == IScannerPlugin::FAIL)
			hasErrors = true;

		next = well.next();
		if (next == '\0')//Missing closing '*/'
			return Token(TokenType::TOKEN_TYPE_ERROR, "/*" + well.get());

		filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);
	}

	if (hasErrors){
		well.merge();
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());
	}

	well.step(-1);
	auto value = well.get();

	well.step(2);
	well.merge();

	return Token(TokenType::TOKEN_TYPE_MULTI_LINE_COMMENT, value, "/*", "*/");
}

bool StructuredScript::Scanner::Plugins::MultiLineComment::matches(ICharacterWell &well){
	return (well.peek(2) == "/*");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::MultiLineComment::type() const{
	return TokenType::TOKEN_TYPE_MULTI_LINE_COMMENT;
}
