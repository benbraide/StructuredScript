#ifndef STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_INTERFACE_H
#define STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_INTERFACE_H

#include <string>

namespace StructuredScript{
	namespace Interfaces{
		class Symbols{
		public:
			virtual ~Symbols(){}

			virtual void init() = 0;

			virtual void clear() = 0;

			virtual void add(const std::string &value) = 0;

			virtual void remove(const std::string &value) = 0;

			virtual std::string find(const std::string &value) const = 0;
		};
	}

	typedef Interfaces::Symbols ISymbols;
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_INTERFACE_H */
