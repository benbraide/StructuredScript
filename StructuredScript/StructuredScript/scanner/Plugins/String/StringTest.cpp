#include "../../../CppUnitLite/TestHarness.h"

#include "String.h"

#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(String, Test){
		Scanner::Plugins::String str;

		Scanner::StringCharacterWell mcw_1("string"), mcw_2("\"double\""), mcw_3("\'single\'"), mcw_4("`back`"),
			mcw_5("@\"double \\nescaped\""), mcw_6("@\"double\\\"escaped\""), mcw_7("\"double unescaped"), mcw_8("\"\\\"double\\\" escaped\"");

		CHECK(str.type() == Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING);

		CHECK(!str.matches(mcw_1));
		CHECK(str.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		CHECK(str.matches(mcw_2));
		CHECK(str.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING, "double"));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "");

		CHECK(str.matches(mcw_3));
		CHECK(str.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING, "single"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		CHECK(str.matches(mcw_4));
		CHECK(str.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BACK_QUOTED_STRING, "back"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		CHECK(str.matches(mcw_5));
		CHECK(str.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_RAW_STRING, "double \\nescaped"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "");

		CHECK(str.matches(mcw_6));
		CHECK(str.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_RAW_STRING, "double\\"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "escaped\"");

		CHECK(str.matches(mcw_7));
		CHECK(str.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "\"double unescaped"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "");

		CHECK(str.matches(mcw_8));
		CHECK(str.get(mcw_8) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING, "\\\"double\\\" escaped"));
		mcw_8.commit();
		CHECK(mcw_8.dump() == "");
	}
}