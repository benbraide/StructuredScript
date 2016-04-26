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
			TOKEN_TYPE_NUMBER,
			TOKEN_TYPE_EXPONENTIATED_NUMBER,
			TOKEN_TYPE_DOUBLE_QUOTED_STRING,
			TOKEN_TYPE_SINGLY_QUOTED_STRING,
			TOKEN_TYPE_BACK_QUOTED_STRING,
			TOKEN_TYPE_IDENTIFIER,
			TOKEN_TYPE_LEFT_UNARY_OPERATOR,
			TOKEN_TYPE_RIGHT_UNARY_OPERATOR,
			TOKEN_TYPE_BINARY_OPERATOR,
			TOKEN_TYPE_TYPENAME,
			TOKEN_TYPE_PRAGMA,
			TOKEN_TYPE_INCLUDE,
			TOKEN_TYPE_DEFINE,
			TOKEN_TYPE_BEGIN,
			TOKEN_TYPE_END,
			TOKEN_TYPE_OPERATOR,
			TOKEN_TYPE_GROUP,
			TOKEN_TYPE_INDEX,
			TOKEN_TYPE_BLOCK,
			TOKEN_TYPE_ANGLE,
			TOKEN_TYPE_ERROR
		};

		enum TokenGroup{
			TOKEN_GROUP_NUMBER,
			TOKEN_GROUP_STRING,
			TOKEN_GROUP_IDENTIFIER,
			TOKEN_GROUP_OPERATOR,
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
		// Method:    tokenIsIdentifierType
		// FullName:  StructuredScript::Scanner::tokenIsIdentifierType
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: TokenType type
		//************************************
		bool tokenIsIdentifierType(TokenType type);

		//************************************
		// Method:    tokenIsOperatorType
		// FullName:  StructuredScript::Scanner::tokenIsOperatorType
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: TokenType type
		//************************************
		bool tokenIsOperatorType(TokenType type);

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
			Token(TokenType type, const std::string &value)
				: type_(type), value_(value){}

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

		private:
			//************************************
			// Method:    getTypeString_
			// FullName:  StructuredScript::Scanner::Token::getTypeString_
			// Access:    private 
			// Returns:   std::string
			// Qualifier: const
			//************************************
			std::string getTypeString_() const;

			TokenType type_;
			std::string value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_SCANNER_TOKEN_H */