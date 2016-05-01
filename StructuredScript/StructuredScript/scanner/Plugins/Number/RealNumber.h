#pragma once

#ifndef STRUCTURED_SCRIPT_REAL_NUMBER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_REAL_NUMBER_SCANNER_PLUGIN_H

#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class RealNumber : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				TokenType get_(ICharacterWell &well, FilterType filter = nullptr) const;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_REAL_NUMBER_SCANNER_PLUGIN_H */