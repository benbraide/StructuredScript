#include "Identifier.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::Identifier::get(ICharacterWell &well, FilterType filter){
	if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto next = well.next();
	auto filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);

	auto hasErrors = false;
	while (next == '_' || next == '$' || ::isalnum(next) || filterState != IScannerPlugin::NONE){
		if (filterState == IScannerPlugin::EXCLUDE)
			break;

		if (!hasErrors && filterState == IScannerPlugin::FAIL)
			hasErrors = true;

		next = well.next();
		filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);
	}

	if (next != '\0')//Move back to exclude character
		well.step(-1);

	if (hasErrors)
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	return Token(TokenType::TOKEN_TYPE_IDENTIFIER, well.get());
}

bool StructuredScript::Scanner::Plugins::Identifier::matches(ICharacterWell &well){
	auto next = well.peek();
	return (next == '_' || next == '$' || ::isalpha(next));
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::Identifier::type() const{
	return TokenType::TOKEN_TYPE_IDENTIFIER;
}
