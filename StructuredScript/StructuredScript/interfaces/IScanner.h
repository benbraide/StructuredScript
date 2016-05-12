#pragma once

#ifndef STRUCTURED_SCRIPT_SCANNER_INTERFACE_H
#define STRUCTURED_SCRIPT_SCANNER_INTERFACE_H

#include <list>

#include "IScannerPlugin.h"

namespace StructuredScript{
	namespace Interfaces{
		class Scanner{
		public:
			typedef std::list<ScannerPlugin *>				PluginListType;
			typedef StructuredScript::Scanner::Token		Token;
			typedef StructuredScript::Scanner::TokenType	TokenType;

			virtual ~Scanner(){}

			virtual void init() = 0;

			virtual Token next(CharacterWell &well, const PluginListType &plugins = {}) = 0;

			virtual Token peek(CharacterWell &well, const PluginListType &plugins = {}) = 0;

			virtual void save(const Token &token) = 0;

			virtual bool fork(char closeWith, bool testBlanks = false) = 0;

			virtual bool fork(const std::string &closeWith, bool matchAll = false, bool testBlanks = false) = 0;

			virtual bool open(CharacterWell &well, char target, char closeWith = '\0', bool testBlanks = false) = 0;

			virtual bool close(CharacterWell &well, bool force = false) = 0;

			virtual bool hasMore(CharacterWell &well) = 0;

			virtual const ScannerPlugin *getPlugin(TokenType target) const = 0;
		};
	}

	typedef Interfaces::Scanner IScanner;
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_INTERFACE_H */