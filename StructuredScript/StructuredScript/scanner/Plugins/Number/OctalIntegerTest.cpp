#include "../../../CppUnitLite/TestHarness.h"

#include "RealNumber.h"
#include "OctalInteger.h"

#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(OctalInteger, Test){
		Scanner::Plugins::RealNumber number;
		Scanner::Plugins::OctalInteger oct(number);

		Scanner::StringCharacterWell mcw_1("string"), mcw_2("4518"), mcw_3("04572"), mcw_4("0000"), mcw_5("0117"), mcw_6("0819"), mcw_7("04572ll");

		CHECK(oct.type() == Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER);

		CHECK(!oct.matches(mcw_1));
		CHECK(oct.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		CHECK(!oct.matches(mcw_2));
		CHECK(oct.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "4518");

		CHECK(oct.matches(mcw_3));
		CHECK(oct.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER, "4572"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		CHECK(oct.matches(mcw_4));
		CHECK(oct.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER, "000"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		CHECK(oct.matches(mcw_5));
		CHECK(oct.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER, "117"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "");

		CHECK(oct.matches(mcw_6));
		CHECK(oct.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "0819"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "");

		CHECK(oct.matches(mcw_7));
		CHECK(oct.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER, "4572"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "ll");
	}
}