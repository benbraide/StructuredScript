#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_PRECEDENCE_H
#define STRUCTURED_SCRIPT_OPERATOR_PRECEDENCE_H

#include <list>
#include <string>

#include "../Interfaces/IOperatorInfo.h"

namespace StructuredScript{
	class OperatorInfo : public IOperatorInfo{
	public:
		typedef std::map<std::string, MatchedListType> ListType;

		virtual void init();

		virtual void clear();

		virtual void add(const std::string &value, const OperatorType &type, const Info &info);

		virtual void remove(const std::string &value, const OperatorType &type, const Info &info);

		virtual void find(const std::string &value, const OperatorType &type, MatchedListType &list) const;

	private:
		ListType entries_;
	};
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_PRECEDENCE_H */