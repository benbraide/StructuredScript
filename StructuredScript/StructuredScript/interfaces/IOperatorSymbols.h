#ifndef STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_INTERFACE_H
#define STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_INTERFACE_H

#include "../Common/OperatorSymbol.h"

namespace StructuredScript{
	namespace Interfaces{
		class OperatorSymbols{
		public:
			virtual ~OperatorSymbols(){}

			virtual void init() = 0;

			virtual void clear() = 0;

			virtual void add(const OperatorInfo &info) = 0;

			virtual void remove(const OperatorInfo &info) = 0;

			virtual OperatorInfo find(const OperatorInfo &info, bool matchAllTypes) const = 0;
		};
	}

	typedef Interfaces::OperatorSymbols IOperatorSymbols;
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_SYMBOLS_INTERFACE_H */
