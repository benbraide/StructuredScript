#pragma once

#ifndef STRUCTURED_SCRIPT_RADIX_INTEGER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_RADIX_INTEGER_SCANNER_PLUGIN_H

#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class RadixInteger : public IScannerPlugin{
			public:
				explicit RadixInteger(const IScannerPlugin &realNumberPlugin)
					: realNumberPlugin_(&realNumberPlugin){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				bool checkAlpha_(char target, int radix) const;

				bool checkDigit_(char target, int radix) const;

				const IScannerPlugin *realNumberPlugin_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_RADIX_INTEGER_SCANNER_PLUGIN_H */