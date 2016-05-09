#pragma once

#ifndef STRUCTURED_SCRIPT_NUMBER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_NUMBER_SCANNER_PLUGIN_H

#include "BinaryInteger.h"
#include "HexadecimalInteger.h"
#include "OctalInteger.h"
#include "RealNumber.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class Number : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				BinaryInteger binaryInteger_;
				HexadecimalInteger hexadecimalInteger_;
				RealNumber realNumber_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_NUMBER_SCANNER_PLUGIN_H */