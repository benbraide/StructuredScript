#include "Symbols.h"

void StructuredScript::Symbols::init(){
	symbols_.clear();

	symbols_.push_back("+");

	symbols_.push_back("-");

	symbols_.push_back("*");

	symbols_.push_back("**");

	symbols_.push_back("/");

	symbols_.push_back("%");

	symbols_.push_back("&");

	symbols_.push_back("^");

	symbols_.push_back("|");

	symbols_.push_back("<<");

	symbols_.push_back(">>");

	symbols_.push_back("~");

	symbols_.push_back("++");

	symbols_.push_back("--");

	symbols_.push_back("&&");

	symbols_.push_back("||");

	symbols_.push_back("!");

	symbols_.push_back("<");

	symbols_.push_back("<=");

	symbols_.push_back("==");

	symbols_.push_back("===");

	symbols_.push_back("!==");

	symbols_.push_back("!=");

	symbols_.push_back(">=");

	symbols_.push_back(">");

	symbols_.push_back("=");

	symbols_.push_back("+=");

	symbols_.push_back("-=");

	symbols_.push_back("*=");

	symbols_.push_back("/=");

	symbols_.push_back("%=");

	symbols_.push_back("&=");

	symbols_.push_back("^=");

	symbols_.push_back("|=");

	symbols_.push_back("<<=");

	symbols_.push_back(">>=");

	symbols_.push_back("?");

	symbols_.push_back(":");

	symbols_.push_back(";");

	symbols_.push_back(".");

	symbols_.push_back(",");

	symbols_.push_back("->");

	symbols_.push_back("::");

	symbols_.push_back("()");

	symbols_.push_back("[]");

	symbols_.push_back("...");

	symbols_.push_back("@");

	symbols_.push_back("#");

	symbols_.push_back("##");
}

void StructuredScript::Symbols::clear(){
	symbols_.clear();
}

void StructuredScript::Symbols::add(const std::string &value){
	if (std::find(symbols_.begin(), symbols_.end(), value) == symbols_.end())
		symbols_.push_back(value);
}

void StructuredScript::Symbols::remove(const std::string &value){
	auto symbol = std::find(symbols_.begin(), symbols_.end(), value);
	if (symbol != symbols_.end())
		symbols_.erase(symbol);
}

std::string StructuredScript::Symbols::find(const std::string &value) const{
	if (value.empty())
		return "";

	std::string matched;
	for (const auto &symbol : symbols_){
		if (symbol.size() > matched.size() && value.find(symbol) == 0u){
			matched = symbol;
			if (matched.size() == value.size())//Full match
				break;
		}
	}

	return matched;
}
