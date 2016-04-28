#include "../../../CppUnitLite/TestHarness.h"

#include "Symbol.h"
#include "../../../Common/OperatorSymbols.h"

#include "../../Wells/StringCharacterWell.h"

namespace StructuredScript{
	TEST(Symbol, Test){
		OperatorSymbols symbols;
		Scanner::Plugins::Symbol sym(symbols);

		symbols.init();
		Scanner::StringCharacterWell mcw_1("string"), mcw_2("$4518"), mcw_3("+"), mcw_4("++"), mcw_5("+++"), mcw_6("==="), mcw_7("[]ll");

		CHECK(sym.type() == Scanner::TokenType::TOKEN_TYPE_SYMBOL);

		CHECK(!sym.matches(mcw_1));
		CHECK(sym.get(mcw_1) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_1.commit();
		CHECK(mcw_1.dump() == "string");

		CHECK(!sym.matches(mcw_2));
		CHECK(sym.get(mcw_2) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_NONE, ""));
		mcw_2.commit();
		CHECK(mcw_2.dump() == "$4518");

		CHECK(sym.matches(mcw_3));
		CHECK(sym.get(mcw_3) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "+"));
		mcw_3.commit();
		CHECK(mcw_3.dump() == "");

		CHECK(sym.matches(mcw_4));
		CHECK(sym.get(mcw_4) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "++"));
		mcw_4.commit();
		CHECK(mcw_4.dump() == "");

		CHECK(sym.matches(mcw_5));
		CHECK(sym.get(mcw_5) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "++"));
		mcw_5.commit();
		CHECK(mcw_5.dump() == "+");

		CHECK(sym.matches(mcw_6));
		CHECK(sym.get(mcw_6) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "==="));
		mcw_6.commit();
		CHECK(mcw_6.dump() == "");

		CHECK(sym.matches(mcw_7));
		CHECK(sym.get(mcw_7) == Scanner::Token(Scanner::TokenType::TOKEN_TYPE_SYMBOL, "[]"));
		mcw_7.commit();
		CHECK(mcw_7.dump() == "ll");
	}
}