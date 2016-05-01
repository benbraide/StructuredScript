#include "RadixInteger.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::RadixInteger::get(ICharacterWell &well, FilterType filter) const{
	if (!matches(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto radixStr = well.get();
	auto radix = std::stoi(radixStr);

	well.step(1);//Skip 'r'
	well.fork();

	auto token = realNumberPlugin_->get(well, [this, filter, radix](char next) -> unsigned short{
		unsigned short state;
		if (filter != nullptr){
			state = filter(next);
			if (state != IScannerPlugin::NONE)
				return state;
		}

		if (next == '0')
			return IScannerPlugin::INCLUDE;

		if (::isalpha(next))
			state = checkAlpha_(next, radix) ? IScannerPlugin::INCLUDE : IScannerPlugin::NONE;
		else if (::isdigit(next))
			state = checkDigit_(next, radix) ? IScannerPlugin::NONE : IScannerPlugin::FAIL;
		else
			state = IScannerPlugin::NONE;

		return state;
	});

	well.merge();
	if (token.getType() != TokenType::TOKEN_TYPE_DECIMAL_INTEGER && token.getType() != TokenType::TOKEN_TYPE_OCTAL_INTEGER)
		return Token(TokenType::TOKEN_TYPE_ERROR, radixStr + "r" + token.getValue());

	return Token(TokenType::TOKEN_TYPE_RADIX_INTEGER, token.str(), radixStr + "r");
}

bool StructuredScript::Scanner::Plugins::RadixInteger::matches(const ICharacterWell &well) const{
	try{
		auto radix = std::stoi(well.get());
		if (radix < 2 || radix > 36)
			return false;
	} catch(...){
		return false;
	}

	return (well.peek() == 'r');
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::RadixInteger::type() const{
	return TokenType::TOKEN_TYPE_RADIX_INTEGER;
}

bool StructuredScript::Scanner::Plugins::RadixInteger::checkAlpha_(char target, int radix) const{
	if (radix < 11)
		return false;

	return (::tolower(target) <= ('a' + (radix - 10)));
}

bool StructuredScript::Scanner::Plugins::RadixInteger::checkDigit_(char target, int radix) const{
	if (radix > 9)
		return true;

	return (target <= ('0' + radix));
}
