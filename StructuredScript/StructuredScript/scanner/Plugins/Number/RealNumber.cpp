#include "RealNumber.h"

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::RealNumber::get_(ICharacterWell &well, FilterType filter) const{
	if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
		return TokenType::TOKEN_TYPE_NONE;

	auto next = well.next();
	auto filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);

	auto hasErrors = false, isReal = false, pointRead = false, eRead = false;
	while (next == '.' || next == 'e' || next == 'E' || ::isdigit(next) || filterState != IScannerPlugin::NONE){
		if (filterState == IScannerPlugin::EXCLUDE)
			break;

		if (!hasErrors && filterState == IScannerPlugin::FAIL)
			hasErrors = true;

		if (!hasErrors && !eRead){//No errors & Number is not fully formed
			if (next == 'e' || next == 'E'){
				next = well.peek();
				if (next == '+' || next == '-')
					well.step(1);

				well.fork();
				auto right = get_(well, filter);
				well.merge();

				if (right == TokenType::TOKEN_TYPE_ERROR || right == TokenType::TOKEN_TYPE_NONE)
					return TokenType::TOKEN_TYPE_ERROR;

				eRead = true;
			}
			else if (next == '.'){
				if (pointRead)//Multiple decimal points encountered -- STOP
					break;
				else
					pointRead = true;
			}
		}
		else if (!hasErrors)
			hasErrors = true;

		next = well.next();
		filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);
	}

	if (next != '\0')//Move back to exclude character
		well.step(-1);

	if (hasErrors)
		return TokenType::TOKEN_TYPE_ERROR;

	if (pointRead){
		if (well.prev() == '.')//Ignore trailing point
			pointRead = false;
		else
			well.step(1);
	}

	if (eRead)
		return TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER;

	if (pointRead)
		return TokenType::TOKEN_TYPE_REAL_NUMBER;

	return TokenType::TOKEN_TYPE_DECIMAL_INTEGER;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::RealNumber::get(ICharacterWell &well, FilterType filter) const{
	auto type = get_(well, filter);
	return Token(type, well.get());
}

bool StructuredScript::Scanner::Plugins::RealNumber::matches(const ICharacterWell &well) const{
	auto next = well.peek();
	return (next == '.' || (next != '0' && ::isdigit(next)) || well.peek(2) == "0.");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::RealNumber::type() const{
	return TokenType::TOKEN_TYPE_REAL_NUMBER;
}
