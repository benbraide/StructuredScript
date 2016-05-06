#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_H
#define STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_H

#include <list>

#include "../Interfaces/ISymbols.h"

namespace StructuredScript{
	class Symbols : public ISymbols{
	public:
		typedef std::list<std::string> ListType;

		virtual void init();

		virtual void clear();

		virtual void add(const std::string &value);

		virtual void remove(const std::string &value);

		virtual std::string find(const std::string &value) const;

	private:
		ListType symbols_;
	};
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_H */