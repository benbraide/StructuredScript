#include "../../../CppUnitLite/TestHarness.h"

#include "RealNumber.h"
#include "HexadecimalInteger.h"

#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(HexadecimalInteger, Test){
		Scanner::Plugins::RealNumber number;
		Scanner::Plugins::HexadecimalInteger hex(number);

		Scanner::StringCharacterWell mcw_1("string"), mcw_2("4518"), mcw_3("0x45"), mcw_4("0x45af"), mcw_5("0xafb"), mcw_6("0xafbll"), mcw_7("0x.279"),
			mcw_8("0x9.279"), mcw_9("0x45e9"), mcw_10("072");

		CHECK(hex.type() == Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER);

		CHECK(!hex.matches(mcw_1));
		CHECK(hex.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		CHECK(!hex.matches(mcw_2));
		CHECK(hex.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "4518");

		CHECK(hex.matches(mcw_3));
		CHECK(hex.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER, "45"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		CHECK(hex.matches(mcw_4));
		CHECK(hex.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER, "45af"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		CHECK(hex.matches(mcw_5));
		CHECK(hex.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER, "afb"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "");

		CHECK(hex.matches(mcw_6));
		CHECK(hex.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER, "afb"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "ll");

		CHECK(hex.matches(mcw_7));
		CHECK(hex.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "0x.279"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "");

		CHECK(hex.matches(mcw_8));
		CHECK(hex.get(mcw_8) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "0x9.279"));
		mcw_8.commit();
		CHECK(mcw_8.dump() == "");

		CHECK(hex.matches(mcw_9));
		CHECK(hex.get(mcw_9) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "0x45e9"));
		mcw_9.commit();
		CHECK(mcw_9.dump() == "");

		CHECK(!hex.matches(mcw_10));
		CHECK(hex.get(mcw_10) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_10.commit();
		CHECK(mcw_10.dump() == "072");
	}
}