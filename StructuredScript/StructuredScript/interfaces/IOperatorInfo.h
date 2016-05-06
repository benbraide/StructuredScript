#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_PRECEDENCE_INTERFACE_H
#define STRUCTURED_SCRIPT_OPERATOR_PRECEDENCE_INTERFACE_H

#include <map>
#include <string>

#include "../Common/OperatorType.h"

namespace StructuredScript{
	namespace Interfaces{
		class OperatorInfo{
		public:
			struct Info{
				short precedence;
				bool isLeftAssociative;
			};

			typedef std::map<OperatorType, Info> MatchedListType;

			virtual ~OperatorInfo(){}

			virtual void init() = 0;

			virtual void clear() = 0;

			virtual void add(const std::string &value, const OperatorType &type, const Info &info) = 0;

			virtual void remove(const std::string &value, const OperatorType &type, const Info &info) = 0;

			virtual void find(const std::string &value, const OperatorType &type, MatchedListType &list) const = 0;
		};
	}

	typedef Interfaces::OperatorInfo IOperatorInfo;
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_PRECEDENCE_INTERFACE_H */