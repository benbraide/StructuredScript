#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_IDENTIFIER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_OPERATOR_IDENTIFIER_SCANNER_PLUGIN_H

#include "../../../Common/EnumAdapter.h"

#include "Identifier.h"
#include "../Symbol/Symbol.h"
#include "../Skip/Skip.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class OperatorIdentifier : public IScannerPlugin{
			public:
				explicit OperatorIdentifier(ISymbols &symbols)
					: symbolPlugin_(symbols){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				Token get_(ICharacterWell &well, TokenType type, const std::string &prefix, FilterType filter) const;

				Token getSymbol_(ICharacterWell &well, TokenType type, const std::string &prefix, FilterType filter) const;

				Token skip_(ICharacterWell &well) const;

				Identifier identifierPlugin_;
				Symbol symbolPlugin_;
				Skip skipPlugin_;
			};

			typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 1> OperatorTokenType;
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_IDENTIFIER_SCANNER_PLUGIN_H */