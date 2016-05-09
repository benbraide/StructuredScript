#include <iostream>

#include "CppUnitLite/TestHarness.h"

#include "Storage/GlobalStorage.h"

#include "Scanner/Scanner.h"
#include "Scanner/Wells/StringCharacterWell.h"
#include "Scanner/Plugins/Number/SignedNumber.h"

#include "Nodes/LiteralNode.h"

StructuredScript::IGlobalStorage *StructuredScript::IGlobalStorage::globalStorage;

int main(){
	TestResult tr;
	TestRegistry::runAllTests(tr);

	StructuredScript::Storage::GlobalStorage globalStorage;
	StructuredScript::IGlobalStorage::globalStorage = &globalStorage;

	globalStorage.init();

	StructuredScript::Scanner::Scanner scanner;
	StructuredScript::Scanner::Plugins::SignedNumber signedNumber;

	scanner.init();
	scanner.operatorSymbols.init();

	std::string input;
	while (true){
		std::cout << "> ";
		std::getline(std::cin, input);
		StructuredScript::Scanner::StringCharacterWell well(input);

		auto token = scanner.next(well, { &signedNumber });
		auto literal = std::make_shared<StructuredScript::Nodes::LiteralNode>(token);
		auto value = literal->evaluate(nullptr, nullptr, nullptr);

		std::cout << literal->str() << "\n";
		if (value == nullptr)
			std::cout << "Error!\n";
		else
			std::cout << value->str(nullptr, nullptr, nullptr) + token.suffix() << "\n";
	}

	return 0;
}