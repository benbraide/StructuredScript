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
				Number()
					: binaryInteger_(realNumber_), hexadecimalInteger_(realNumber_), octalInteger_(realNumber_){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				BinaryInteger binaryInteger_;
				HexadecimalInteger hexadecimalInteger_;
				OctalInteger octalInteger_;
				RealNumber realNumber_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_NUMBER_SCANNER_PLUGIN_H */