#pragma once

#ifndef STRUCTURED_SCRIPT_LITERAL_NODE_H
#define STRUCTURED_SCRIPT_LITERAL_NODE_H

#include <cmath>

#include "../Common/Factory.h"
#include "../Interfaces/INode.h"

#include "../Scanner/Scanner.h"
#include "../Scanner/Suffix.h"

namespace StructuredScript{
	namespace Nodes{
		class LiteralNode : public INode{
		public:
			explicit LiteralNode(const Scanner::Token &value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

		protected:
			IAny::Ptr evaluateNumber_(IStorage *storage, IExceptionManager *exception, INode *expr);

			template <typename Type>
			Type getValue_() const;

			long double parseExponent_() const;

			std::string escapeString_() const;

			Scanner::Token value_;
		};

		template <typename Type>
		Type StructuredScript::Nodes::LiteralNode::getValue_() const{
			switch (value_.type()){
			case Scanner::TokenType::TOKEN_TYPE_DECIMAL_INTEGER:
				return static_cast<Type>(std::stoll(value_.value()));
			case Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER:
				return static_cast<Type>(std::stoll(value_.value(), nullptr, 16));
			case Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER:
				return static_cast<Type>(std::stoll(value_.value(), nullptr, 8));
			case Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER:
				return static_cast<Type>(std::stoll(value_.value(), nullptr, 2));
			case Scanner::TokenType::TOKEN_TYPE_RADIX_INTEGER:
				return static_cast<Type>(std::stoll(value_.value(), nullptr, std::stoi(value_.prefix())));
			case Scanner::TokenType::TOKEN_TYPE_EXPONENTIATED_NUMBER:
				return static_cast<Type>(parseExponent_());
			default:
				break;
			}

			return static_cast<Type>(std::stold(value_.value()));
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_LITERAL_NODE_H */