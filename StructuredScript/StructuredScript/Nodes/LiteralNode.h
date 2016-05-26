#pragma once

#ifndef STRUCTURED_SCRIPT_LITERAL_NODE_H
#define STRUCTURED_SCRIPT_LITERAL_NODE_H

#include <cmath>

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "../Scanner/Scanner.h"
#include "../Scanner/Suffix.h"

#include "../Scanner/Plugins/Number/HexadecimalInteger.h"
#include "../Scanner/Plugins/Number/OctalInteger.h"

#include "../Scanner/Wells/StringCharacterWell.h"

namespace StructuredScript{
	namespace Nodes{
		class LiteralNode : public INode, public ILiteralNode{
		public:
			explicit LiteralNode(const Scanner::Token &value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual void value(const Scanner::Token &value) override;

			virtual Scanner::Token value() override;

		protected:
			IAny::Ptr evaluateNumber_(IStorage *storage, IExceptionManager *exception, INode *expr);

			template <typename Type>
			Type getValue_() const;

			template <typename Type>
			Type getIntegerValue_(const std::string &value, int base) const;

			long double parseExponent_() const;

			std::string escapeString_(IExceptionManager *exception, INode *expr) const;

			char getEscapedCharacter_(char value) const;

			Scanner::Token value_;
		};

		template <typename Type>
		Type StructuredScript::Nodes::LiteralNode::getValue_() const{
			switch (value_.type()){
			case Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER:
				return getIntegerValue_<Type>(value_.value(), 10);
			case Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER:
				return getIntegerValue_<Type>(value_.value(), 16);
			case Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER:
				return getIntegerValue_<Type>(value_.value(), 8);
			case Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER:
				return getIntegerValue_<Type>(value_.value(), 2);
			case Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER:
				return getIntegerValue_<Type>(value_.value(), std::stoi(value_.prefix()));
			case Scanner::TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER:
				return static_cast<Type>(parseExponent_());
			default:
				break;
			}

			return static_cast<Type>(std::stold(value_.value()));
		}

		template <typename Type>
		Type StructuredScript::Nodes::LiteralNode::getIntegerValue_(const std::string &value, int base) const{
			if (value.empty() || value[0] == '-')
				return static_cast<Type>(std::stoll(value_.value(), nullptr, base));

			return static_cast<Type>(std::stoull(value_.value(), nullptr, base));
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_LITERAL_NODE_H */