#pragma once

#ifndef STRUCTURED_SCRIPT_TYPENAME_IDENTIFIER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_TYPENAME_IDENTIFIER_SCANNER_PLUGIN_H

#include "../../../Common/Typename.h"
#include "../../../Common/EnumAdapter.h"
#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class TypenameIdentifier : public IScannerPlugin{
			public:
				TypenameIdentifier(const IScannerPlugin &identifierPlugin, const IScannerPlugin &skipPlugin)
					: identifierPlugin_(&identifierPlugin), skipPlugin_(&skipPlugin){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				Token get_(ICharacterWell &well, FilterType filter) const;

				Token getLong_(ICharacterWell &well, FilterType filter) const;

				Token getUnsigned_(ICharacterWell &well, FilterType filter) const;

				Token skip_(ICharacterWell &well) const;

				Typename getTypename_(const std::string &value) const;

				const IScannerPlugin *identifierPlugin_;
				const IScannerPlugin *skipPlugin_;
			};

			typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 4> TypenameTokenType;
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_TYPENAME_IDENTIFIER_SCANNER_PLUGIN_H */