#pragma once

#ifndef STRUCTURED_SCRIPT_RADIX_INTEGER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_RADIX_INTEGER_SCANNER_PLUGIN_H

#include "DecimalInteger.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class RadixInteger : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) override;

				virtual bool matches(ICharacterWell &well) override;

				virtual TokenType type() const override;

			private:
				bool checkAlpha_(char target, int radix) const;

				bool checkDigit_(char target, int radix) const;

				DecimalInteger decimalInteger_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_RADIX_INTEGER_SCANNER_PLUGIN_H */