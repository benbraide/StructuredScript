#pragma once

#ifndef STRUCTURED_SCRIPT_SYMBOL_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_SYMBOL_SCANNER_PLUGIN_H

#include "../../../Interfaces/ISymbols.h"
#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class Symbol : public IScannerPlugin{
			public:
				explicit Symbol(ISymbols &symbols)
					: symbols_(&symbols){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				ISymbols *symbols_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_SYMBOL_SCANNER_PLUGIN_H */