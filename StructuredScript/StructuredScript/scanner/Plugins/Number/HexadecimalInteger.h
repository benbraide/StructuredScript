#pragma once

#ifndef STRUCTURED_SCRIPT_HEXADECIMAL_INTEGER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_HEXADECIMAL_INTEGER_SCANNER_PLUGIN_H

#include "DecimalInteger.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class HexadecimalInteger : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) override;

				virtual bool matches(ICharacterWell &well) override;

				virtual TokenType type() const override;

			private:
				DecimalInteger decimalInteger_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_HEXADECIMAL_INTEGER_SCANNER_PLUGIN_H */