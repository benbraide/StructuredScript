#pragma once

#ifndef STRUCTURED_SCRIPT_SCANNER_H
#define STRUCTURED_SCRIPT_SCANNER_H

#include <memory>

#include "../Interfaces/IScanner.h"
#include "../Common/Symbols.h"

#include "Plugins/Identifier/Identifier.h"
#include "Plugins/Identifier/TypenameIdentifier.h"

#include "Plugins/Number/Number.h"
#include "Plugins/Number/RadixInteger.h"

#include "Plugins/String/String.h"
#include "Plugins/Symbol/Symbol.h"

#include "Plugins/Skip/Skip.h"

namespace StructuredScript{
	namespace Scanner{
		typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 3> NaNTokenType;
		typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 4> TrueTokenType;
		typedef StaticEnumAdapter<TokenType, TokenType::TOKEN_TYPE_ERROR, 5> FalseTokenType;

		class Scanner : public IScanner{
		public:
			struct CloseInfo{
				std::string value;
				bool matchAll;
				bool testBlanks;
			};

			typedef std::list<Token>		TokenListType;
			typedef std::list<CloseInfo>	OpenListType;

			virtual Token next(ICharacterWell &well, const PluginListType &plugins = {}) override;

			virtual Token peek(ICharacterWell &well, const PluginListType &plugins = {}) override;

			virtual void save(const Token &token) override;

			virtual bool fork(char closeWith, bool testBlanks = false) override;

			virtual bool fork(const std::string &closeWith, bool matchAll = false, bool testBlanks = false) override;

			virtual bool open(ICharacterWell &well, char target, char closeWith = '\0', bool testBlanks = false) override;

			virtual bool close(ICharacterWell &well, bool force = false) override;

			virtual bool hasMore(ICharacterWell &well) override;

			virtual const IScannerPlugin *getPlugin(TokenType target) const override;

			static void init();

			static Symbols operatorSymbols;

		private:
			Token get_(ICharacterWell &well, const PluginListType &plugins);

			Token extendIdentifier_(ICharacterWell &well, const Token &token);

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
			CloseInfo closeWith_ = CloseInfo{ "", true, false };
			TokenListType savedTokens_;

			static PluginListType plugins_;

			static Plugins::Identifier identifierPlugin_;
			static Plugins::TypenameIdentifier typenameIdentifierPlugin_;

			static Plugins::Number numberPlugin_;
			static Plugins::RadixInteger radixIntegerPlugin_;

			static Plugins::Symbol symbolPlugin_;

			static Plugins::String stringPlugin_;
			static Plugins::Skip skipPlugin_;
		};

		//************************************
		// Method:    tokenIsLiteralType
		// FullName:  StructuredScript::Scanner::tokenIsLiteralType
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: TokenType type
		//************************************
		bool tokenIsLiteralType(TokenType type);
	}
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_H */