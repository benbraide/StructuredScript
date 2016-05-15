#include "TypenameIdentifier.h"

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::TypenameIdentifier::get(ICharacterWell &well, FilterType filter) const{
	auto value = well.get();
	auto type = getTypename_(value);

	if (type == Typename::TYPE_NAME_LONG)
		return getLong_(well, filter);

	if (type == Typename::TYPE_NAME_UINT)
		return getUnsigned_(well, filter);

	if (type == Typename::TYPE_NAME_NONE)
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	return Token(TypenameTokenType::type, value);
}

bool StructuredScript::Scanner::Plugins::TypenameIdentifier::matches(const ICharacterWell &well) const{
	auto value = well.get();
	return (value == "any" || value == "void" || value == "bool" || value == "bit" || value == "byte" || value == "char" || value == "short" ||
		value == "int" || value == "long" || value == "float" || value == "double" || value == "string" || value == "unsigned");
}

StructuredScript::Scanner::TokenType StructuredScript::Scanner::Plugins::TypenameIdentifier::type() const{
	return TokenType::TOKEN_TYPE_IDENTIFIER;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::TypenameIdentifier::get_(ICharacterWell &well, FilterType filter) const{
	well.fork();

	auto blank = skip_(well);
	if (blank.type() == TokenType::TOKEN_TYPE_ERROR){
		well.merge();
		return blank;
	}

	return identifierPlugin_.get(well, filter);
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::TypenameIdentifier::getLong_(ICharacterWell &well, FilterType filter) const{
	auto token = get_(well, filter);
	if (token.type() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, "long " + token.value());

	auto type = getTypename_(token.value());
	if (type == Typename::TYPE_NAME_NONE)
		well.collapse();//Rollback

	well.merge();
	if (type == Typename::TYPE_NAME_LONG)//long long
		return Token(TypenameTokenType::type, "long long");

	if (type == Typename::TYPE_NAME_DOUBLE)//long double
		return Token(TypenameTokenType::type, "long double");

	if (type != Typename::TYPE_NAME_NONE)//long *typename" -- ERROR
		return Token(TokenType::TOKEN_TYPE_ERROR, "long " + token.value());

	return Token(TypenameTokenType::type, "long");
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::TypenameIdentifier::getUnsigned_(ICharacterWell &well, FilterType filter) const{
	auto token = get_(well, filter);
	if (token.type() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, "unsigned " + token.value());

	auto type = getTypename_(token.value());
	if (type == Typename::TYPE_NAME_NONE)
		well.collapse();//Rollback

	well.merge();
	if (type == Typename::TYPE_NAME_CHAR)//unsigned char
		return Token(TypenameTokenType::type, "unsigned char");

	if (type == Typename::TYPE_NAME_SHORT)//unsigned short
		return Token(TypenameTokenType::type, "unsigned short");

	if (type == Typename::TYPE_NAME_INT)//unsigned int
		return Token(TypenameTokenType::type, "unsigned int");

	if (type == Typename::TYPE_NAME_LONG){//unsigned (long | long long)
		token = getLong_(well, filter);
		if (token.type() == TokenType::TOKEN_TYPE_ERROR)
			return Token(TokenType::TOKEN_TYPE_ERROR, "unsigned long " + token.value());

		auto value = token.value();
		if (value == "long double")//unsigned long double -- ERROR
			return Token(TokenType::TOKEN_TYPE_ERROR, "unsigned long double");

		if (value == "long long")//unsigned long long
			return Token(TypenameTokenType::type, "unsigned long long");

		return Token(TypenameTokenType::type, "unsigned long");
	}

	if (type != Typename::TYPE_NAME_NONE)//unsigned *typename" -- ERROR
		return Token(TokenType::TOKEN_TYPE_ERROR, "unsigned " + token.value());

	return Token(TokenType::TOKEN_TYPE_ERROR, "unsigned");//unsigned -- ERROR
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Plugins::TypenameIdentifier::skip_(ICharacterWell &well) const{
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

StructuredScript::Typename StructuredScript::Scanner::Plugins::TypenameIdentifier::getTypename_(const std::string &value) const{
	if (value == "any")
		return Typename::TYPE_NAME_ANY;

	if (value == "void")
		return Typename::TYPE_NAME_VOID;

	if (value == "bool")
		return Typename::TYPE_NAME_BOOLEAN;

	if (value == "bit")
		return Typename::TYPE_NAME_BIT;

	if (value == "byte")
		return Typename::TYPE_NAME_BYTE;

	if (value == "char")
		return Typename::TYPE_NAME_CHAR;

	if (value == "short")
		return Typename::TYPE_NAME_SHORT;

	if (value == "int")
		return Typename::TYPE_NAME_INT;

	if (value == "long")
		return Typename::TYPE_NAME_LONG;

	if (value == "float")
		return Typename::TYPE_NAME_FLOAT;

	if (value == "double")
		return Typename::TYPE_NAME_DOUBLE;

	if (value == "string")
		return Typename::TYPE_NAME_STRING;

	if (value == "unsigned")
		return Typename::TYPE_NAME_UINT;

	return Typename::TYPE_NAME_NONE;
}
