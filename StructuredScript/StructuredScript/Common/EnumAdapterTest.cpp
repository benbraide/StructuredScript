#include "../CppUnitLite/TestHarness.h"

#include "EnumAdapter.h"
#include "../Scanner/Token.h"

namespace StructuredScript{
	TEST(EnumAdapter, Test){
		EnumAdapter<Scanner::TokenType, static_cast<int>(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER)> number;

		CHECK(number == Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER);
		CHECK(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER == number);

		CHECK(number == static_cast<int>(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER));
		CHECK(static_cast<int>(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER) == number);

		EnumAdapter<Scanner::TokenType, 72> oob;

		CHECK(oob == static_cast<Scanner::TokenType>(72));
		CHECK(static_cast<Scanner::TokenType>(72) == oob);

		CHECK(oob == 72);
		CHECK(72 == oob);
	}
}