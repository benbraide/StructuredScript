#include "../CppUnitLite/TestHarness.h"

#include "Scanner.h"

#include "Plugins/Number/SignedNumber.h"
#include "Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(Scanner, Test){
		Scanner::Scanner scanner;
		Scanner::StringCharacterWell well("var value = -45 / -45 + 0x72ffb ** 036 ? 0b1001 : 4r320, \"hello\" + @`world` :: === + $ - /*ignore*/ aye;//fin");

		std::string types = "any void bool bit byte char unsigned char short unsigned short int unsigned int long; unsigned long;";
		types += "long long unsigned long long float double long double string str unsigned; unsigned float unsigned long double long bit";

		Scanner::StringCharacterWell typeWell(types);
		Scanner::Plugins::SignedNumber signedNumber;

		scanner.init();
		scanner.operatorSymbols.init();

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "var"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "value"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "="));
		CHECK(scanner.next(well, { &signedNumber }) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "-45"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "/"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "-"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "45"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "+"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER, "72ffb"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "**"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER, "36"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "?"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER, "1001"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ":"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER, "320"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ","));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING, "hello"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "+"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BACK_QUOTED_RAW_STRING, "world"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "::"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "==="));
		CHECK(scanner.next(well, { &signedNumber }) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "+"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "$"));

		CHECK(scanner.next(well, { &signedNumber }) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "-"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "aye"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "any"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "void"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "bool"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "bit"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "byte"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "char"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "unsigned char"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "short"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "unsigned short"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "int"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "unsigned int"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "long"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "unsigned long"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "long long"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "unsigned long long"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "float"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "double"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "long double"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, "string"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "str"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "unsigned"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "unsigned float"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "unsigned long double"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "long bit"));
	}
}