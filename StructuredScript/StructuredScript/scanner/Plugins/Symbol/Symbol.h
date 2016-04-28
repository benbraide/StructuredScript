#pragma once

#ifndef STRUCTURED_SCRIPT_SYMBOL_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_SYMBOL_SCANNER_PLUGIN_H

#include "../../../Interfaces/IOperatorSymbols.h"
#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class Symbol : public IScannerPlugin{
			public:
				Symbol(IOperatorSymbols &symbols)
					: symbols_(&symbols){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				IOperatorSymbols *symbols_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_SYMBOL_SCANNER_PLUGIN_H */