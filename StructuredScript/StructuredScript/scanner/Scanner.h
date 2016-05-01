#pragma once

#ifndef STRUCTURED_SCRIPT_SCANNER_H
#define STRUCTURED_SCRIPT_SCANNER_H

#include <memory>

#include "../Interfaces/IScanner.h"
#include "../Common/OperatorSymbols.h"

#include "Plugins/Identifier/Identifier.h"
#include "Plugins/Identifier/OperatorIdentifier.h"
#include "Plugins/Identifier/TypenameIdentifier.h"

#include "Plugins/Number/Number.h"
#include "Plugins/Number/RadixInteger.h"

#include "Plugins/String/String.h"
#include "Plugins/Symbol/Symbol.h"

#include "Plugins/Skip/Skip.h"

namespace StructuredScript{
	namespace Scanner{
		class Scanner : public IScanner{
		public:
			typedef std::list<Token>	TokenListType;
			typedef std::list<char>		OpenListType;

			virtual void init() override;

			virtual Token next(ICharacterWell &well, const PluginListType &plugins = {}) override;

			virtual Token peek(ICharacterWell &well, const PluginListType &plugins = {}) override;

			virtual void save(const Token &token) override;

			virtual bool open(ICharacterWell &well, char target, char closeWith = '\0') override;

			virtual bool close(ICharacterWell &well) override;

			virtual bool hasMore(ICharacterWell &well) override;

			virtual const IScannerPlugin *getPlugin(TokenType target) const override;

			static OperatorSymbols operatorSymbols;

		private:
			Token get_(ICharacterWell &well, const PluginListType &plugins);

			Token extendIdentifier_(ICharacterWell &well, const Token &token);

			Token extendTypenameIdentifier_(ICharacterWell &well, const Token &token);

			Token extendDecimalInteger_(ICharacterWell &well, const Token &token);

			Token extendNumber_(ICharacterWell &well, const Token &token);

			Token extendSymbol_(ICharacterWell &well, const Token &token);

			Token getSaved_(bool remove);

			void dropSaved_();

			char getCloseWith_(char target) const;

			bool verifyTarget_(ICharacterWell &well, char target, bool check);

			bool hasMore_(ICharacterWell &well, bool check);

			Token skip_(ICharacterWell &well) const;

			OpenListType openList_;
			char closeWith_ = '\0';

			TokenListType savedTokens_;
			PluginListType plugins_;

			static Plugins::Identifier identifierPlugin_;
			static Plugins::OperatorIdentifier operatorIdentifierPlugin_;
			static Plugins::TypenameIdentifier typenameIdentifierPlugin_;

			static Plugins::Number numberPlugin_;
			static Plugins::RadixInteger radixIntegerPlugin_;

			static Plugins::Symbol symbolPlugin_;

			static Plugins::String stringPlugin_;
			static Plugins::Skip skipPlugin_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_H */