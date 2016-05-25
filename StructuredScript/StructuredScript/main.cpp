#include "CppUnitLite/TestHarness.h"

#include "Storage/GlobalStorage.h"
#include "Common/OperatorInfo.h"
#include "Common/ExceptionManager.h"

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
	globalStorage.path("Includes");

	std::string input;
	StructuredScript::Parser::Parser parser;
	StructuredScript::ExceptionManager xManager;

	while (true){
		std::cout << "> ";
		std::getline(std::cin, input);

		StructuredScript::Scanner::Scanner scanner;
		StructuredScript::Scanner::StringCharacterWell well(input);

		auto node = parser.parse(well, scanner, &xManager);
		if (xManager.has()){
			if (xManager.hasBreak())
				std::cout << "'break' found outside loop!\n";
			else if (xManager.hasContinue())
				std::cout << "'continue' found outside loop!\n";
			else if (xManager.hasReturn())
				std::cout << "'return' found outside function!\n";
			else
				std::cout << xManager.get()->str(nullptr, nullptr, nullptr) << "\n";

			xManager.clear();
			continue;
		}

		node->evaluate(&globalStorage, &xManager, nullptr);
		if (xManager.has()){
			if (xManager.hasBreak())
				std::cout << "'break' found outside loop!\n";
			else if (xManager.hasContinue())
				std::cout << "'continue' found outside loop!\n";
			else if (xManager.hasReturn())
				std::cout << "'return' found outside function!\n";
			else
				std::cout << xManager.get()->str(nullptr, nullptr, nullptr) << "\n";

			xManager.clear();
		}
	}

	return 0;
}
