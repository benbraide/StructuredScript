#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_IDENTIFIER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_OPERATOR_IDENTIFIER_SCANNER_PLUGIN_H

#include "../../../Common/EnumAdapter.h"
#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class OperatorIdentifier : public IScannerPlugin{
			public:
				OperatorIdentifier(IScannerPlugin &identifierPlugin, IScannerPlugin &symbolPlugin, IScannerPlugin &skipPlugin)
					: identifierPlugin_(&identifierPlugin), symbolPlugin_(&symbolPlugin), skipPlugin_(&skipPlugin){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				Token get_(ICharacterWell &well, TokenType type, const std::string &prefix, FilterType filter) const;

				Token getSymbol_(ICharacterWell &well, TokenType type, const std::string &prefix, FilterType filter) const;

				Token skip_(ICharacterWell &well) const;

				IScannerPlugin *identifierPlugin_;
				IScannerPlugin *symbolPlugin_;
				IScannerPlugin *skipPlugin_;
			};

			typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 1> LeftUnaryOperatorTokenType;
			typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 2> RightUnaryOperatorTokenType;
			typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 3> BinaryOperatorTokenType;
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_IDENTIFIER_SCANNER_PLUGIN_H */