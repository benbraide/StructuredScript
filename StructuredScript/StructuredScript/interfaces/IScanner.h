#pragma once

#ifndef STRUCTURED_SCRIPT_SCANNER_INTERFACE_H
#define STRUCTURED_SCRIPT_SCANNER_INTERFACE_H

#include <list>

#include "IScannerPlugin.h"

namespace StructuredScript{
	namespace Interfaces{
		class Scanner{
		public:
			typedef std::list<IScannerPlugin *>				PluginListType;
			typedef StructuredScript::Scanner::Token		Token;
			typedef StructuredScript::Scanner::TokenType	TokenType;

			virtual ~Scanner(){}

			virtual void init() = 0;

			virtual Token next(ICharacterWell &well, const PluginListType &plugins = {}) = 0;

			virtual Token peek(ICharacterWell &well, const PluginListType &plugins = {}) = 0;

			virtual void save(const Token &token) = 0;

			virtual bool open(ICharacterWell &well, char target, char closeWith = '\0') = 0;

			virtual bool close(ICharacterWell &well) = 0;

			virtual bool hasMore(ICharacterWell &well) = 0;

			virtual const IScannerPlugin *getPlugin(TokenType target) const = 0;
		};
	}

	typedef Interfaces::Scanner IScanner;
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_INTERFACE_H */