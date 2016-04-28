#include "../../../CppUnitLite/TestHarness.h"

#include "String.h"

#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(String, Test){
		Scanner::Plugins::DoubleQuotedString dqs;
		Scanner::Plugins::DoubleQuotedRawString dqrs;
		Scanner::Plugins::SinglyQuotedString sqs;
		Scanner::Plugins::BackQuotedString bqs;

		Scanner::StringCharacterWell mcw_1("string"), mcw_2("\"double\""), mcw_3("\'single\'"), mcw_4("`back`"),
			mcw_5("\"double \\nescaped\""), mcw_6("\"double\\\"escaped\""), mcw_7("\"double\\\"escaped");

		CHECK(dqs.type() == Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_STRING);
		CHECK(dqrs.type() == Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_RAW_STRING);
		CHECK(sqs.type() == Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING);
		CHECK(bqs.type() == Scanner::TokenType::TOKEN_TYPE_BACK_QUOTED_STRING);

		CHECK(!dqs.matches(mcw_1) && !dqrs.matches(mcw_1) && !sqs.matches(mcw_1) && !bqs.matches(mcw_1));
		CHECK(dqs.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		CHECK(dqs.matches(mcw_2) && dqrs.matches(mcw_2) && !sqs.matches(mcw_2) && !bqs.matches(mcw_2));
		CHECK(sqs.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(bqs.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(dqrs.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_RAW_STRING, "double"));
		mcw_2.collapse();
		CHECK(dqs.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_STRING, "double"));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "");

		CHECK(!dqs.matches(mcw_3) && !dqrs.matches(mcw_3) && sqs.matches(mcw_3) && !bqs.matches(mcw_3));
		CHECK(dqs.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(bqs.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(dqrs.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(sqs.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING, "single"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		CHECK(!dqs.matches(mcw_4) && !dqrs.matches(mcw_4) && !sqs.matches(mcw_4) && bqs.matches(mcw_4));
		CHECK(dqs.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(sqs.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(dqrs.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(bqs.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_BACK_QUOTED_STRING, "back"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		CHECK(dqs.matches(mcw_5) && dqrs.matches(mcw_5) && !sqs.matches(mcw_5) && !bqs.matches(mcw_5));
		CHECK(sqs.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(bqs.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(dqrs.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_RAW_STRING, "double \\nescaped"));
		mcw_5.collapse();
		CHECK(dqs.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_STRING, "double \\nescaped"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "");

		CHECK(dqs.matches(mcw_6) && dqrs.matches(mcw_6) && !sqs.matches(mcw_6) && !bqs.matches(mcw_6));
		CHECK(sqs.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(bqs.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(dqrs.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_RAW_STRING, "double\\"));
		mcw_6.collapse();
		CHECK(dqs.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_STRING, "double\\\"escaped"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "");

		CHECK(dqs.matches(mcw_7) && dqrs.matches(mcw_7) && !sqs.matches(mcw_7) && !bqs.matches(mcw_7));
		CHECK(sqs.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(bqs.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		CHECK(dqrs.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_DOUBLE_QUOTED_RAW_STRING, "double\\"));
		mcw_7.collapse();
		CHECK(dqs.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "\"double\\\"escaped"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "");
	}
}