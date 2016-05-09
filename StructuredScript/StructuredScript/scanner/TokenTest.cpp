#include "../CppUnitLite/TestHarness.h"

#include "token.h"

namespace StructuredScript{
	TEST(Token, Test){
		CHECK(tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER));
		CHECK(tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER));
		CHECK(tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER));
		CHECK(tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER));

		CHECK(!tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING));
		CHECK(!tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER));
		CHECK(!tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_SYMBOL));
		CHECK(!tokenIsNumberType(Scanner::TokenType::TOKEN_TYPE_GROUP));

		CHECK(tokenIsStringType(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING));
		CHECK(tokenIsStringType(Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING));
		CHECK(tokenIsStringType(Scanner::TokenType::TOKEN_TYPE_BACK_QUOTED_STRING));

		CHECK(!tokenIsStringType(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER));
		CHECK(!tokenIsStringType(Scanner::TokenType::TOKEN_TYPE_IDENTIFIER));
		CHECK(!tokenIsStringType(Scanner::TokenType::TOKEN_TYPE_SYMBOL));
		CHECK(!tokenIsStringType(Scanner::TokenType::TOKEN_TYPE_GROUP));

		CHECK(tokenIsGroupType(Scanner::TokenType::TOKEN_TYPE_GROUP));
		CHECK(tokenIsGroupType(Scanner::TokenType::TOKEN_TYPE_INDEX));
		CHECK(tokenIsGroupType(Scanner::TokenType::TOKEN_TYPE_BLOCK));
		CHECK(tokenIsGroupType(Scanner::TokenType::TOKEN_TYPE_ANGLE));

		CHECK(!tokenIsGroupType(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER));
		CHECK(!tokenIsGroupType(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING));
		CHECK(!tokenIsGroupType(Scanner::TokenType::TOKEN_TYPE_SYMBOL));

		Scanner::Token number(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "18");

		CHECK(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER == number.type());
		CHECK(Scanner::TokenGroup::TOKEN_GROUP_NUMBER == number.group());

		CHECK("18" == number.value());
		CHECK("18" == number.str());

		CHECK(number.isGroup(Scanner::TokenGroup::TOKEN_GROUP_NUMBER));
		CHECK(!number.isError());
	}
}