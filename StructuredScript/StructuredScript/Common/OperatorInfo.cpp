#include "OperatorInfo.h"

void StructuredScript::OperatorInfo::init(){
	entries_.clear();

	entries_[";"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 0, true } },
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 1, true } },
		{ OperatorType(OperatorType::RIGHT_UNARY), Info{ 1, true } }
	};

	entries_[","] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 2, true } }
	};

	entries_[":"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 3, true } }
	};

	entries_["="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["+="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["-="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["*="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["/="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["%="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["&="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["^="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["|="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["<<="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_[">>="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, false } }
	};

	entries_["?"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 4, true } }
	};

	entries_["||"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 5, true } }
	};

	entries_["&&"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 6, true } }
	};

	entries_["|"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 7, true } }
	};

	entries_["^"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 8, true } }
	};

	entries_["&"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 9, true } },
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } }
	};

	entries_["=="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 10, true } }
	};

	entries_["==="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 10, true } }
	};

	entries_["!="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 10, true } }
	};

	entries_["!=="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 10, true } }
	};

	entries_["<"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 11, true } }
	};

	entries_["<="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 11, true } }
	};

	entries_[">"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 11, true } }
	};

	entries_[">="] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 11, true } }
	};

	entries_["..."] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 12, true } },
		{ OperatorType(OperatorType::RIGHT_UNARY), Info{ 20, true } }
	};

	entries_["<<"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 13, true } }
	};

	entries_[">>"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 13, true } }
	};

	entries_["+"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 14, true } },
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } }
	};

	entries_["-"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 14, true } },
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } }
	};

	entries_["*"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 15, true } },
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } }
	};

	entries_["/"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 15, true } }
	};

	entries_["%"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 15, true } }
	};

	entries_["**"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 16, true } }
	};

	entries_["~"] = MatchedListType{
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } }
	};

	entries_["!"] = MatchedListType{
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } }
	};

	entries_["++"] = MatchedListType{
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } },
		{ OperatorType(OperatorType::RIGHT_UNARY), Info{ 18, true } }
	};

	entries_["--"] = MatchedListType{
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 17, true } },
		{ OperatorType(OperatorType::RIGHT_UNARY), Info{ 18, true } }
	};

	entries_["()"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 18, true } },
		{ OperatorType(OperatorType::RIGHT_UNARY), Info{ 18, true } }
	};

	entries_["[]"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 18, true } },
		{ OperatorType(OperatorType::RIGHT_UNARY), Info{ 18, true } }
	};

	entries_["."] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 19, true } }
	};

	entries_["->"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 19, true } }
	};

	entries_["::"] = MatchedListType{
		{ OperatorType(OperatorType::BINARY), Info{ 21, true } },
		{ OperatorType(OperatorType::LEFT_UNARY), Info{ 22, true } }
	};
}

void StructuredScript::OperatorInfo::clear(){
	entries_.clear();
}

void StructuredScript::OperatorInfo::add(const std::string &value, const OperatorType &type, const Info &info){
	if (type.isNone())
		return;

	auto entry = entries_.find(value);
	auto &target = (entry == entries_.end()) ? entries_[value] : entry->second;

	if (type.hasType(OperatorType::LEFT_UNARY))
		target[OperatorType(OperatorType::LEFT_UNARY)] = info;

	if (type.hasType(OperatorType::RIGHT_UNARY))
		target[OperatorType(OperatorType::RIGHT_UNARY)] = info;

	if (type.hasType(OperatorType::BINARY))
		target[OperatorType(OperatorType::BINARY)] = info;
}

void StructuredScript::OperatorInfo::remove(const std::string &value, const OperatorType &type, const Info &info){
	auto entry = entries_.find(value);
	if (entry == entries_.end())
		return;

	if (!type.isNone()){
		if (type.hasType(OperatorType::LEFT_UNARY))
			entry->second.erase(OperatorType(OperatorType::LEFT_UNARY));

		if (type.hasType(OperatorType::RIGHT_UNARY))
			entry->second.erase(OperatorType(OperatorType::RIGHT_UNARY));

		if (type.hasType(OperatorType::BINARY))
			entry->second.erase(OperatorType(OperatorType::BINARY));
	}
	else//Remove all
		entry->second.clear();

	if (entry->second.empty())//Empty info list -- Delete entry
		entries_.erase(entry);
}

void StructuredScript::OperatorInfo::find(const std::string &value, const OperatorType &type, MatchedListType &list) const{
	auto entry = entries_.find(value);
	if (entry == entries_.end())
		return;

	for (const auto &info : entry->second){
		if (type.hasType(info.first.getTypes()))
			list[info.first] = info.second;
	}
}
