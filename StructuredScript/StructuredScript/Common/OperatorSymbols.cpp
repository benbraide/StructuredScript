#include "OperatorSymbols.h"

void StructuredScript::OperatorSymbols::init(){
	symbols_.clear();

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_PLUS,
		"+",
		OperatorSymbol::LEFT_UNARY | OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_MINUS,
		"-",
		OperatorSymbol::LEFT_UNARY | OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_TIMES,
		"*",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_POWER,
		"**",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_DIVIDE,
		"/",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_MODULO,
		"%",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_BITWISE_AND,
		"&",
		OperatorSymbol::LEFT_UNARY | OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_BITWISE_XOR,
		"^",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_BITWISE_OR,
		"|",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_LEFT_SHIFT,
		"<<",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_RIGHT_SHIFT,
		">>",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_BITWISE_INVERSE,
		"~",
		OperatorSymbol::LEFT_UNARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_INCREMENT,
		"++",
		OperatorSymbol::LEFT_UNARY | OperatorSymbol::RIGHT_UNARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_DECREMENT,
		"--",
		OperatorSymbol::LEFT_UNARY | OperatorSymbol::RIGHT_UNARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_AND,
		"&&",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_OR,
		"||",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_NOT,
		"!",
		OperatorSymbol::LEFT_UNARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_LESS,
		"<",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_LESS_OR_EQUALS,
		"<=",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_EQUALS,
		"==",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_STRICTLY_EQUALS,
		"===",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_STRICTLY_NOT_EQUAL,
		"!==",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_NOT_EQUAL,
		"!=",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_GREATER_OR_EQUALS,
		">=",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_GREATER,
		">",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_BITWISE_OR,
		"|",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_ASSIGNMENT,
		"=",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_SELECTION,
		"?",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_COLON,
		":",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_SEMICOLON,
		";",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_PERIOD,
		".",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_COMMA,
		",",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_ACCESS,
		"->",
		OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_SCOPE,
		"::",
		OperatorSymbol::LEFT_UNARY | OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_GROUP,
		"()",
		OperatorSymbol::RIGHT_UNARY | OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_INDEX,
		"[]",
		OperatorSymbol::RIGHT_UNARY | OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_ELLIPSIS,
		"...",
		OperatorSymbol::RIGHT_UNARY | OperatorSymbol::BINARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_AT,
		"@",
		OperatorSymbol::LEFT_UNARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_POUND,
		"#",
		OperatorSymbol::LEFT_UNARY
	}));

	symbols_.push_back(OperatorSymbol(OperatorInfo{
		SymbolType::SYMBOL_TYPE_DOUBLE_POUND,
		"##",
		OperatorSymbol::BINARY
	}));
}

void StructuredScript::OperatorSymbols::clear(){
	symbols_.clear();
}

void StructuredScript::OperatorSymbols::add(const OperatorInfo &info){
	auto symbol = find_(info, false);
	if (symbol == symbols_.end())
		symbols_.push_back(OperatorSymbol(info));
	else
		symbol->addType(info.types);
}

void StructuredScript::OperatorSymbols::remove(const OperatorInfo &info){
	auto symbol = find_(info, false);
	if (symbol == symbols_.end())
		return;

	if (info.types == OperatorSymbol::NONE)
		symbol->removeTypes();
	else
		symbol->removeType(info.types);

	if (symbol->isNone())
		symbols_.erase(symbol);
}

StructuredScript::OperatorInfo StructuredScript::OperatorSymbols::find(const OperatorInfo &info, bool matchAllTypes) const{
	auto symbol = find_(info, matchAllTypes);
	return (symbol == symbols_.end()) ? OperatorInfo{ SymbolType::SYMBOL_TYPE_NONE, "", OperatorSymbol::NONE } : symbol->getInfo();
}

StructuredScript::OperatorSymbols::ListType::iterator StructuredScript::OperatorSymbols::find_(const OperatorInfo &info, bool matchAllTypes){
	for (auto symbol = symbols_.begin(); symbol != symbols_.end(); ++symbol){
		if (symbol->matches(info, matchAllTypes))
			return symbol;
	}

	return symbols_.end();
}

StructuredScript::OperatorSymbols::ListType::const_iterator StructuredScript::OperatorSymbols::find_(const OperatorInfo &info, bool matchAllTypes) const{
	ListType::const_iterator matched = symbols_.end();
	for (auto symbol = symbols_.begin(); symbol != symbols_.end(); ++symbol){
		if (symbol->matches(info, matchAllTypes) && (matched == symbols_.end() || symbol->getValue().size() > matched->getValue().size())){
			matched = symbol;
			if (matched->getValue().size() == info.value.size())//Full match
				break;
		}
	}

	return matched;
}
