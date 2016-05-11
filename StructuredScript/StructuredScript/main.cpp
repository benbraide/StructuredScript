#include <iostream>

#include "CppUnitLite/TestHarness.h"

#include "Storage/GlobalStorage.h"
#include "Common/OperatorInfo.h"

#include "Scanner/Scanner.h"
#include "Scanner/Wells/StringCharacterWell.h"

#include "Parser/Parser.h"

StructuredScript::IGlobalStorage *StructuredScript::IGlobalStorage::globalStorage;

int main(){
	TestResult tr;
	TestRegistry::runAllTests(tr);

	StructuredScript::Storage::GlobalStorage globalStorage;
	StructuredScript::IGlobalStorage::globalStorage = &globalStorage;

	globalStorage.init();

	StructuredScript::Parser::Parser::operatorInfo.init();
	StructuredScript::Parser::Parser parser;
	StructuredScript::Scanner::Scanner scanner;

	scanner.init();
	scanner.operatorSymbols.init();

	std::string input;
	while (true){
		std::cout << "> ";
		std::getline(std::cin, input);
		StructuredScript::Scanner::StringCharacterWell well(input);

		auto node = parser.parse(well, scanner, nullptr);
		auto value = node->evaluate(&globalStorage, nullptr, nullptr);

		std::cout << node->str() << "\n";
		if (value == nullptr)
			std::cout << "Error!\n";
		else
			std::cout << value->str(nullptr, nullptr, nullptr) << "\n";
	}

	return 0;
}
