#include "../../../CppUnitLite/TestHarness.h"

#include "RealNumber.h"
#include "BinaryInteger.h"

#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(BinaryInteger, Test){
		Scanner::Plugins::RealNumber number;
		Scanner::Plugins::BinaryInteger bin(number);

		Scanner::StringCharacterWell mcw_1("string"), mcw_2("4518"), mcw_3("0b101"), mcw_4("0b000"), mcw_5("0b111"), mcw_6("0b45"), mcw_7("0b1010ll");

		CHECK(bin.type() == Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER);

		CHECK(!bin.matches(mcw_1));
		CHECK(bin.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		CHECK(!bin.matches(mcw_2));
		CHECK(bin.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "4518");

		CHECK(bin.matches(mcw_3));
		CHECK(bin.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER, "101"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		CHECK(bin.matches(mcw_4));
		CHECK(bin.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER, "000"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		CHECK(bin.matches(mcw_5));
		CHECK(bin.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER, "111"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "");

		CHECK(bin.matches(mcw_6));
		CHECK(bin.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "0b45"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "");

		CHECK(bin.matches(mcw_7));
		CHECK(bin.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER, "1010"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "ll");
	}
}