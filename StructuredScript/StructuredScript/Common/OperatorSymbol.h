#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_H
#define STRUCTURED_SCRIPT_OPERATOR_H

#include <string>

namespace StructuredScript{
	enum SymbolType{
		SYMBOL_TYPE_NONE,
		SYMBOL_TYPE_PLUS,
		SYMBOL_TYPE_MINUS,
		SYMBOL_TYPE_TIMES,
		SYMBOL_TYPE_DIVIDE,
		SYMBOL_TYPE_MODULO,
		SYMBOL_TYPE_POWER,
		SYMBOL_TYPE_BITWISE_INVERSE,
		SYMBOL_TYPE_BITWISE_AND,
		SYMBOL_TYPE_BITWISE_OR,
		SYMBOL_TYPE_BITWISE_XOR,
		SYMBOL_TYPE_LEFT_SHIFT,
		SYMBOL_TYPE_RIGHT_SHIFT,
		SYMBOL_TYPE_LESS,
		SYMBOL_TYPE_GREATER,
		SYMBOL_TYPE_EQUALS,
		SYMBOL_TYPE_STRICTLY_EQUALS,
		SYMBOL_TYPE_LESS_OR_EQUALS,
		SYMBOL_TYPE_GREATER_OR_EQUALS,
		SYMBOL_TYPE_NOT_EQUAL,
		SYMBOL_TYPE_STRICTLY_NOT_EQUAL,
		SYMBOL_TYPE_NOT,
		SYMBOL_TYPE_AND,
		SYMBOL_TYPE_OR,
		SYMBOL_TYPE_ASSIGNMENT,
		SYMBOL_TYPE_COLON,
		SYMBOL_TYPE_SEMICOLON,
		SYMBOL_TYPE_COMMA,
		SYMBOL_TYPE_PERIOD,
		SYMBOL_TYPE_ACCESS,
		SYMBOL_TYPE_ELLIPSIS,
		SYMBOL_TYPE_GROUP,
		SYMBOL_TYPE_INDEX,
		SYMBOL_TYPE_INCREMENT,
		SYMBOL_TYPE_DECREMENT,
		SYMBOL_TYPE_SCOPE,
		SYMBOL_TYPE_SELECTION,
		SYMBOL_TYPE_POUND,
		SYMBOL_TYPE_DOUBLE_POUND,
		SYMBOL_TYPE_AT,
		SYMBOL_TYPE_CUSTOM
	};

	struct OperatorInfo{
		SymbolType symbol;
		std::string value;
		unsigned short types;
	};

	class OperatorSymbol{
	public:
		explicit OperatorSymbol(const OperatorInfo &info)
			: info_(info){}

		void addType(unsigned short type){
			info_.types |= type;
		}

		void removeType(unsigned short type){
			info_.types &= ~type;
		}

		void removeTypes(){
			info_.types = NONE;
		}

		bool hasType(unsigned short type, bool all) const{
			return all ? ((info_.types & type) == type) : ((info_.types & type) != 0u);
		}

		bool isLeftUnary() const{
			return ((info_.types & LEFT_UNARY) == LEFT_UNARY);
		}

		bool isRightUnary() const{
			return ((info_.types & RIGHT_UNARY) == RIGHT_UNARY);
		}

		bool isBinary() const{
			return ((info_.types & BINARY) == BINARY);
		}

		bool isUnaryOnly() const{
			return ((info_.types & BINARY) != BINARY);
		}

		bool isBinaryOnly() const{
			return (info_.types == BINARY);
		}

		bool isNone() const{
			return (info_.types == NONE);
		}

		bool matches(const OperatorInfo &info, bool all) const{
			return ((info.symbol == SymbolType::SYMBOL_TYPE_NONE || info.symbol == info_.symbol) &&
				(info.types == NONE || hasType(info.types, all))) ? (info.value.find(info_.value) == 0u) : false;
		}

		SymbolType getSymbolType() const{
			return info_.symbol;
		}

		std::string getValue() const{
			return info_.value;
		}

		unsigned short getTypes() const{
			return info_.types;
		}

		const OperatorInfo &getInfo() const{
			return info_;
		}

		static const unsigned short NONE			= 0x0000;
		static const unsigned short LEFT_UNARY		= 0x0001;
		static const unsigned short RIGHT_UNARY		= 0x0002;
		static const unsigned short BINARY			= 0x0004;

	private:
		OperatorInfo info_;
	};
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_H */