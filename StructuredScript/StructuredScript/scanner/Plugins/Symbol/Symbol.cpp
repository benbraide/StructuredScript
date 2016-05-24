#include "Symbol.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::Symbol::get(ICharacterWell &well, FilterType filter){
	if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto next = well.next();
	auto filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);

	auto hasErrors = false;
	while ((next != '_' && next != '$' && ::ispunct(next)) || filterState != IScannerPlugin::NONE){
		if (filterState == IScannerPlugin::EXCLUDE)
			break;

		if (!hasErrors && filterState == IScannerPlugin::FAIL)
			hasErrors = true;

		next = well.next();
		filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);
	}

	if (next != '\0')//Move back to exclude character
		well.step(-1);

	auto value = well.get();
	if (hasErrors)
		return Token(TokenType::TOKEN_TYPE_ERROR, value);

	auto symbol = symbols_->find(value);
	if (symbol.empty()){//Operator not defined
		well.collapse();
		return Token(TokenType::TOKEN_TYPE_NONE, "");
	}

	//If partial match, ignore unmatched characters
	well.step(static_cast<int>(symbol.size() - value.size()));

	return Token(TokenType::TOKEN_TYPE_SYMBOL, symbol);
}

bool StructuredScript::Scanner::Plugins::Symbol::matches(ICharacterWell &well){
	auto next = well.peek();
	return (next != '_' && next != '$' && ::ispunct(next));
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::Symbol::type() const{
	return TokenType::TOKEN_TYPE_SYMBOL;
}
