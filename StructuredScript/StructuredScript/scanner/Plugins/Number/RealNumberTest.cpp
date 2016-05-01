#include "../../../CppUnitLite/TestHarness.h"

#include "RealNumber.h"
#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(RealNumber, Test){
		Scanner::Plugins::RealNumber number;
		Scanner::StringCharacterWell mcw_1("string"), mcw_2("4518"), mcw_3("4518.279"), mcw_4("9e+90"), mcw_5("9e36"), mcw_6("72ll"), mcw_7(".279"),
			mcw_8("0.279"), mcw_9("81."), mcw_10("072"), mcw_11("45fab"), mcw_12("45fab"), mcw_13("45.18.279"), mcw_14("9e"), mcw_15("9e+-90");

		CHECK(number.type() == Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER);

		CHECK(!number.matches(mcw_1));
		CHECK(number.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		CHECK(number.matches(mcw_2));
		CHECK(number.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "4518"));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "");

		CHECK(number.matches(mcw_3));
		CHECK(number.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER, "4518.279"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		CHECK(number.matches(mcw_4));
		CHECK(number.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER, "9e+90"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		CHECK(number.matches(mcw_5));
		CHECK(number.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER, "9e36"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "");

		CHECK(number.matches(mcw_6));
		CHECK(number.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "72"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "ll");

		CHECK(number.matches(mcw_7));
		CHECK(number.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER, ".279"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "");

		CHECK(number.matches(mcw_8));
		CHECK(number.get(mcw_8) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER, "0.279"));
		mcw_8.commit();
		CHECK(mcw_8.dump() == "");

		CHECK(number.matches(mcw_9));
		CHECK(number.get(mcw_9) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "81"));
		mcw_9.commit();
		CHECK(mcw_9.dump() == ".");

		CHECK(!number.matches(mcw_10));
		CHECK(number.get(mcw_10) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_10.commit();
		CHECK(mcw_10.dump() == "072");

		CHECK(number.matches(mcw_11));
		CHECK(number.get(mcw_11) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "45"));
		mcw_11.commit();
		CHECK(mcw_11.dump() == "fab");

		CHECK(number.matches(mcw_12));
		CHECK(number.get(mcw_12, [](char next){
			return (next >= 'a' && next <= 'f') ? IScannerPlugin::INCLUDE : IScannerPlugin::NONE;
		}) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER, "45fab"));
		mcw_12.commit();
		CHECK(mcw_12.dump() == "");

		CHECK(number.matches(mcw_13));
		CHECK(number.get(mcw_13) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_REAL_NUMBER, "45.18"));
		mcw_13.commit();
		CHECK(mcw_13.dump() == ".279");

		CHECK(number.matches(mcw_14));
		CHECK(number.get(mcw_14) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "9e"));
		mcw_14.commit();
		CHECK(mcw_14.dump() == "");

		CHECK(number.matches(mcw_15));
		CHECK(number.get(mcw_15) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "9e+"));
		mcw_15.commit();
		CHECK(mcw_15.dump() == "-90");
	}
}