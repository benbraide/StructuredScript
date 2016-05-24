#pragma once

#ifndef STRUCTURED_SCRIPT_TYPENAME_IDENTIFIER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_TYPENAME_IDENTIFIER_SCANNER_PLUGIN_H

#include "../../../Common/Typename.h"
#include "../../../Common/EnumAdapter.h"

#include "Identifier.h"
#include "../Skip/Skip.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class TypenameIdentifier : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) override;

				virtual bool matches(ICharacterWell &well) override;

				virtual TokenType type() const override;

			private:
				Token get_(ICharacterWell &well, FilterType filter);

				Token getLong_(ICharacterWell &well, FilterType filter);

				Token getUnsigned_(ICharacterWell &well, FilterType filter);

				Token skip_(ICharacterWell &well);

				Typename getTypename_(const std::string &value) const;

				Identifier identifierPlugin_;
				Skip skipPlugin_;
			};

			typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 2> TypenameTokenType;
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_TYPENAME_IDENTIFIER_SCANNER_PLUGIN_H */