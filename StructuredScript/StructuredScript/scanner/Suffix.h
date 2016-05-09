#pragma once

#ifndef STRUCTURED_SCRIPT_SCANNER_SUFFIX_H
#define STRUCTURED_SCRIPT_SCANNER_SUFFIX_H

#include <string>

namespace StructuredScript{
	namespace Scanner{
		enum SuffixType{
			SUFFIX_TYPE_NONE,
			SUFFIX_TYPE_UNSIGNED,
			SUFFIX_TYPE_SHORT,
			SUFFIX_TYPE_USHORT,
			SUFFIX_TYPE_LONG,
			SUFFIX_TYPE_ULONG,
			SUFFIX_TYPE_LLONG,
			SUFFIX_TYPE_ULLONG,
			SUFFIX_TYPE_FLOAT,
			SUFFIX_TYPE_ERROR
		};

		class Suffix{
		public:
			static SuffixType get(const std::string &target);

			static bool isCompatibleWithInteger(SuffixType suffix);

			static bool isCompatibleWithRealNumber(SuffixType suffix);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_SUFFIX_H */