#include "Suffix.h"

StructuredScript::Scanner::SuffixType StructuredScript::Scanner::Suffix::get(const std::string &target){
	if (target.empty())
		return SuffixType::SUFFIX_TYPE_NONE;

	auto first = ::tolower(target[0]);
	if (target.size() == 1u){
		if (first == 'u')
			return SuffixType::SUFFIX_TYPE_UNSIGNED;
		if (first == 'h')
			return SuffixType::SUFFIX_TYPE_SHORT;
		if (first == 'l')
			return SuffixType::SUFFIX_TYPE_LONG;
		if (first == 'f')
			return SuffixType::SUFFIX_TYPE_FLOAT;
	}
	else if (target.size() == 2u){
		auto second = ::tolower(target[1]);
		if (first == 'u' && second == 'h')
			return SuffixType::SUFFIX_TYPE_USHORT;
		if (first == 'u' && second == 'l')
			return SuffixType::SUFFIX_TYPE_ULONG;
		if (first == 'l' && second == 'l')
			return SuffixType::SUFFIX_TYPE_LLONG;
	}
	else if (target.size() == 3u){
		if (first == 'u' && ::tolower(target[1]) == 'l' && ::tolower(target[2]) == 'l')
			return SuffixType::SUFFIX_TYPE_ULLONG;
	}

	return SuffixType::SUFFIX_TYPE_ERROR;
}

bool StructuredScript::Scanner::Suffix::isCompatibleWithInteger(SuffixType suffix){
	return (suffix != SuffixType::SUFFIX_TYPE_FLOAT);
}

bool StructuredScript::Scanner::Suffix::isCompatibleWithRealNumber(SuffixType suffix){
	return (suffix == SuffixType::SUFFIX_TYPE_NONE || suffix == SuffixType::SUFFIX_TYPE_LONG || suffix == SuffixType::SUFFIX_TYPE_FLOAT);
}
