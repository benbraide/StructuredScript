#pragma once

#ifndef STRUCTURED_SCRIPT_SIGNED_NUMBER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_SIGNED_NUMBER_SCANNER_PLUGIN_H

#include "Number.h"
#include "../Skip/Skip.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class SignedNumber : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) override;

				virtual bool matches(ICharacterWell &well) override;

				virtual TokenType type() const override;

			private:
				Token skip_(ICharacterWell &well);

				Number numberPlugin_;
				Skip skipPlugin_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_SIGNED_NUMBER_SCANNER_PLUGIN_H */