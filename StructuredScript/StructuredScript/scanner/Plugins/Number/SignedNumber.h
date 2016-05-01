#pragma once

#ifndef STRUCTURED_SCRIPT_SIGNED_NUMBER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_SIGNED_NUMBER_SCANNER_PLUGIN_H

#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class SignedNumber : public IScannerPlugin{
			public:
				explicit SignedNumber(const IScannerPlugin &numberPlugin, const IScannerPlugin &skipPlugin)
					: numberPlugin_(&numberPlugin), skipPlugin_(&skipPlugin){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				Token skip_(ICharacterWell &well) const;

				const IScannerPlugin *numberPlugin_;
				const IScannerPlugin *skipPlugin_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_SIGNED_NUMBER_SCANNER_PLUGIN_H */