#include "../../../CppUnitLite/TestHarness.h"

#include "RealNumber.h"
#include "RadixInteger.h"

#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(RadixInteger, Test){
		Scanner::Plugins::RealNumber number;
		Scanner::Plugins::RadixInteger rad(number);

		Scanner::StringCharacterWell mcw_1("string"), mcw_2("4518"), mcw_3("0r45"), mcw_4("2r11001"), mcw_5("16rafb"), mcw_6("16rafbll"), mcw_7("10r.279"),
			mcw_8("10r9.279"), mcw_9("8r459"), mcw_10("8r072");

		CHECK(rad.type() == Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER);

		number.get(mcw_1);
		CHECK(!rad.matches(mcw_1));
		CHECK(rad.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		number.get(mcw_2);
		CHECK(!rad.matches(mcw_2));
		CHECK(rad.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "");

		number.get(mcw_3);
		CHECK(!rad.matches(mcw_3));
		CHECK(rad.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "0r45");

		number.get(mcw_4);
		CHECK(rad.matches(mcw_4));
		CHECK(rad.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER, "11001"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		number.get(mcw_5);
		CHECK(rad.matches(mcw_5));
		CHECK(rad.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER, "afb"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "");

		number.get(mcw_6);
		CHECK(rad.matches(mcw_6));
		CHECK(rad.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER, "afb"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "ll");

		number.get(mcw_7);
		CHECK(rad.matches(mcw_7));
		CHECK(rad.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "10r.279"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "");

		number.get(mcw_8);
		CHECK(rad.matches(mcw_8));
		CHECK(rad.get(mcw_8) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "10r9.279"));
		mcw_8.commit();
		CHECK(mcw_8.dump() == "");

		number.get(mcw_9);
		CHECK(rad.matches(mcw_9));
		CHECK(rad.get(mcw_9) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "8r459"));
		mcw_9.commit();
		CHECK(mcw_9.dump() == "");

		number.get(mcw_10);
		CHECK(rad.matches(mcw_10));
		CHECK(rad.get(mcw_10) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER, "072"));
		mcw_10.commit();
		CHECK(mcw_10.dump() == "");
	}
}