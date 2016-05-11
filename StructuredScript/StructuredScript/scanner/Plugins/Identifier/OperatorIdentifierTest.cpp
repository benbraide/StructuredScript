#include "../../../CppUnitLite/TestHarness.h"

#include "OperatorIdentifier.h"

#include "Identifier.h"
#include "../Symbol/Symbol.h"
#include "../Skip/Skip.h"

#include "../../../Common/Symbols.h"
#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(OperatorIdentifier, Test){
		Symbols symbols;
		Scanner::Plugins::Symbol sym(symbols);

		Scanner::Plugins::Identifier id;
		Scanner::Plugins::OperatorIdentifier opId(symbols);

		symbols.init();
		Scanner::StringCharacterWell mcw_1("string"), mcw_2("$4518"), mcw_3("operator +"), mcw_4("operator ++"),
			mcw_5("operator +++"), mcw_6("operator new"), mcw_7("operator[]ll"), mcw_8("operator");

		CHECK(opId.type() == Scanner::TokenType::TOKEN_TYPE_IDENTIFIER);

		id.get(mcw_1);
		CHECK(!opId.matches(mcw_1));
		CHECK(opId.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "");

		id.get(mcw_2);
		CHECK(!opId.matches(mcw_2));
		CHECK(opId.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "");

		id.get(mcw_3);
		CHECK(opId.matches(mcw_3));
		CHECK(opId.get(mcw_3) == Scanner::Token(Scanner::Plugins::OperatorTokenType::type, "+"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		id.get(mcw_4);
		CHECK(opId.matches(mcw_4));
		CHECK(opId.get(mcw_4) == Scanner::Token(Scanner::Plugins::OperatorTokenType::type, "++"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		id.get(mcw_5);
		CHECK(opId.matches(mcw_5));
		CHECK(opId.get(mcw_5) == Scanner::Token(Scanner::Plugins::OperatorTokenType::type, "++"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "+");

		id.get(mcw_6);
		CHECK(opId.matches(mcw_6));
		CHECK(opId.get(mcw_6) == Scanner::Token(Scanner::Plugins::OperatorTokenType::type, "new"));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "");

		id.get(mcw_7);
		CHECK(opId.matches(mcw_7));
		CHECK(opId.get(mcw_7) == Scanner::Token(Scanner::Plugins::OperatorTokenType::type, "[]"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "ll");

		id.get(mcw_8);
		CHECK(opId.matches(mcw_8));
		CHECK(opId.get(mcw_8) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_ERROR, "operator"));
		mcw_8.commit();
		CHECK(mcw_8.dump() == "");
	}
}