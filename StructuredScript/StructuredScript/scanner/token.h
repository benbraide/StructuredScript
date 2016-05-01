#pragma once

#ifndef STRUCTURED_SCRIPT_SCANNER_TOKEN_H
#define STRUCTURED_SCRIPT_SCANNER_TOKEN_H

#include <string>

namespace StructuredScript{
	namespace Scanner{
		enum TokenType{
			TOKEN_TYPE_NONE,
			TOKEN_TYPE_DECIMAL_INTEGER,
			TOKEN_TYPE_HEXADECIMAL_INTEGER,
			TOKEN_TYPE_OCTAL_INTEGER,
			TOKEN_TYPE_BINARY_INTEGER,
			TOKEN_TYPE_RADIX_INTEGER,
			TOKEN_TYPE_REAL_NUMBER,
			TOKEN_TYPE_EXPONENTIATED_NUMBER,
			TOKEN_TYPE_DOUBLY_QUOTED_STRING,
			TOKEN_TYPE_DOUBLY_QUOTED_RAW_STRING,
			TOKEN_TYPE_SINGLY_QUOTED_STRING,
			TOKEN_TYPE_SINGLY_QUOTED_RAW_STRING,
			TOKEN_TYPE_BACK_QUOTED_STRING,
			TOKEN_TYPE_BACK_QUOTED_RAW_STRING,
			TOKEN_TYPE_IDENTIFIER,
			TOKEN_TYPE_SYMBOL,
			TOKEN_TYPE_GROUP,
			TOKEN_TYPE_INDEX,
			TOKEN_TYPE_BLOCK,
			TOKEN_TYPE_ANGLE,
			TOKEN_TYPE_BLANK,
			TOKEN_TYPE_SINGLE_LINE_COMMENT,
			TOKEN_TYPE_MULTI_LINE_COMMENT,
			TOKEN_TYPE_PREPROCESSOR,
			TOKEN_TYPE_ERROR
		};

		enum TokenGroup{
			TOKEN_GROUP_NUMBER,
			TOKEN_GROUP_INTEGER,
			TOKEN_GROUP_REAL,
			TOKEN_GROUP_STRING,
			TOKEN_GROUP_GROUP
		};

		//************************************
		// Method:    tokenIsNumberType
		// FullName:  StructuredScript::Scanner::tokenIsNumberType
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: TokenType type
		//************************************
		bool tokenIsNumberType(TokenType type);

		//************************************
		// Method:    tokenIsStringType
		// FullName:  StructuredScript::Scanner::tokenIsStringType
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: TokenType type
		//************************************
		bool tokenIsStringType(TokenType type);

		//************************************
		// Method:    tokenIsGroupType
		// FullName:  StructuredScript::Scanner::tokenIsGroupType
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: TokenType type
		//************************************
		bool tokenIsGroupType(TokenType type);

		class Token{
		public:
			Token(TokenType type, const std::string &value, const std::string &prefix = "", const std::string &suffix = "",
				bool skipValue = false)
				: type_(type), value_(value), prefix_(prefix), suffix_(suffix), skipValue_(skipValue){}

			//************************************
			// Method:    operator==
			// FullName:  StructuredScript::Scanner::Token::operator==
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: const Token & right
			//************************************
			bool operator ==(const Token &right) const;

			//************************************
			// Method:    operator!=
			// FullName:  StructuredScript::Scanner::Token::operator!=
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: const Token & right
			//************************************
			bool operator !=(const Token &right) const;

			//************************************
			// Method:    getType
			// FullName:  StructuredScript::Scanner::Token::getType
			// Access:    public 
			// Returns:   TokenType
			// Qualifier: const
			//************************************
			TokenType getType() const;

			//************************************
			// Method:    getValue
			// FullName:  StructuredScript::Scanner::Token::getValue
			// Access:    public 
			// Returns:   std::string
			// Qualifier: const
			//************************************
			std::string getValue() const;

			//************************************
			// Method:    str
			// FullName:  StructuredScript::Scanner::Token::str
			// Access:    public 
			// Returns:   std::string
			// Qualifier: const
			//************************************
			std::string str() const;

			//************************************
			// Method:    getPrefix
			// FullName:  StructuredScript::Scanner::Token::getPrefix
			// Access:    public 
			// Returns:   std::string
			// Qualifier: const
			//************************************
			std::string getPrefix() const;

			//************************************
			// Method:    getSuffix
			// FullName:  StructuredScript::Scanner::Token::getSuffix
			// Access:    public 
			// Returns:   std::string
			// Qualifier: const
			//************************************
			std::string getSuffix() const;

			//************************************
			// Method:    getGroup
			// FullName:  StructuredScript::Scanner::Token::getGroup
			// Access:    public 
			// Returns:   StructuredScript::Scanner::TokenGroup
			// Qualifier: const
			//************************************
			TokenGroup getGroup() const;

			//************************************
			// Method:    isGroup
			// FullName:  StructuredScript::Scanner::Token::isGroup
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: TokenGroup group
			//************************************
			bool isGroup(TokenGroup group) const;

			//************************************
			// Method:    isError
			// FullName:  StructuredScript::Scanner::Token::isError
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool isError() const;

			//************************************
			// Method:    isValid
			// FullName:  StructuredScript::Scanner::Token::isValid
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool isValid() const;

		private:
			TokenType type_;
			std::string value_;
			std::string prefix_;
			std::string suffix_;
			bool skipValue_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_TOKEN_H */