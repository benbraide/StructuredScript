#include "../CppUnitLite/TestHarness.h"

#include "Scanner.h"

#include "Plugins/Number/SignedNumber.h"
#include "Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(Scanner, Test){
		Scanner::Scanner scanner;
		Scanner::StringCharacterWell well("var value = -45 / -45 + 0x72ffb ** 036 ? 0b1001 : 4r320, \"hello\" + @`world` :: operator () === + $ - /*ignore*/ aye;//fin");

		std::string types = "any any<integer> void bool bit byte char unsigned char short unsigned short int unsigned int long; unsigned long;";
		types += "long long unsigned long long float double long double string str unsigned; unsigned float unsigned long double long bit";

		Scanner::StringCharacterWell typeWell(types);

		scanner.init();
		Scanner::Plugins::SignedNumber signedNumber(*scanner.getPlugin(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER),
			*scanner.getPlugin(Scanner::TokenType::TOKEN_TYPE_BLANK));

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
		CHECK(scanner.next(well) == Scanner::Token(Scanner::Plugins::BinaryOperatorTokenType::type, "()"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "==="));
		CHECK(scanner.next(well, { &signedNumber }) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "+"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "$"));

		CHECK(scanner.next(well, { &signedNumber }) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "-"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "aye"));

		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));
		CHECK(scanner.next(well) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_ANY)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_ANY)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_VOID)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_BOOLEAN)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_BIT)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_BYTE)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_CHAR)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_UCHAR)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_SHORT)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_USHORT)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_INT)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_UINT)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_LONG)));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_ULONG)));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_LLONG)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_ULLONG)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_FLOAT)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_DOUBLE)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_LDOUBLE)));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::Plugins::TypenameTokenType::type, std::to_string(Typename::TYPE_NAME_STRING)));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER, "str"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "unsigned"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, ";"));

		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "unsigned float"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "unsigned long double"));
		CHECK(scanner.next(typeWell) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "long bit"));
	}
}