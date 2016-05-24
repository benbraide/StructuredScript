#include "Blank.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::Blank::get(ICharacterWell &well, FilterType filter){
	if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto next = well.next();
	while (next == '\0' && well.load())
		next = well.next();

	auto filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);

	auto hasErrors = false;
	while (::isspace(next) || filterState != IScannerPlugin::NONE){
		if (filterState == IScannerPlugin::EXCLUDE)
			break;

		if (!hasErrors && filterState == IScannerPlugin::FAIL)
			hasErrors = true;

		next = well.next();
		while (next == '\0' && well.load())
			next = well.next();

		filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);
	}

	if (next != '\0')//Move back to exclude character
		well.step(-1);

	if (hasErrors)
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	return Token(TokenType::TOKEN_TYPE_BLANK, well.get());
}

bool StructuredScript::Scanner::Plugins::Blank::matches(ICharacterWell &well){
	return (::isspace(well.peek()) != 0);
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::Blank::type() const{
	return TokenType::TOKEN_TYPE_BLANK;
}
