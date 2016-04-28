#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_H
#define STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_H

#include <list>

#include "../Interfaces/IOperatorSymbols.h"

namespace StructuredScript{
	class OperatorSymbols : public IOperatorSymbols{
	public:
		typedef std::list<OperatorSymbol> ListType;

		virtual void init();

		virtual void clear();

		virtual void add(const OperatorInfo &info);

		virtual void remove(const OperatorInfo &info);

		virtual OperatorInfo find(const OperatorInfo &info, bool matchAllTypes) const;

	private:
		ListType::iterator find_(const OperatorInfo &info, bool matchAllTypes);

		ListType::const_iterator find_(const OperatorInfo &info, bool matchAllTypes) const;

		ListType symbols_;
	};
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_H */