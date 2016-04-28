#pragma once

#ifndef STRUCTURED_SCRIPT_SCANNER_PLUGIN_INTERFACE_H
#define STRUCTURED_SCRIPT_SCANNER_PLUGIN_INTERFACE_H

#include <functional>

#include "ICharacterWell.h"
#include "../Scanner/token.h"

namespace StructuredScript{
	namespace Interfaces{
		class ScannerPlugin{
		public:
			typedef std::function<unsigned short (char)> FilterType;

			virtual ~ScannerPlugin(){}

			//************************************
			// Method:    get
			// FullName:  StructuredScript::Scanner::Plugins::DecimalInteger::get
			// Access:    virtual public 
			// Returns:   StructuredScript::Scanner::Token
			// Qualifier: const
			// Parameter: ICharacterWell & well
			//************************************
			virtual Scanner::Token get(ICharacterWell &well, FilterType filter = nullptr) const = 0;

			//************************************
			// Method:    matches
			// FullName:  StructuredScript::Scanner::Plugins::DecimalInteger::matches
			// Access:    virtual public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: const ICharacterWell & well
			//************************************
			virtual bool matches(const ICharacterWell &well) const = 0;

			//************************************
			// Method:    type
			// FullName:  StructuredScript::Scanner::Plugins::DecimalInteger::type
			// Access:    virtual public 
			// Returns:   Scanner::TokenType
			// Qualifier: const
			//************************************
			virtual Scanner::TokenType type() const = 0;

			static const unsigned short NONE		= 0x0000;
			static const unsigned short INCLUDE		= 0x0001;
			static const unsigned short EXCLUDE		= 0x0002;
			static const unsigned short FAIL		= 0x0003;
		};
	}

	typedef Interfaces::ScannerPlugin IScannerPlugin;
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_PLUGIN_INTERFACE_H */