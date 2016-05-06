#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_TYPE_H
#define STRUCTURED_SCRIPT_OPERATOR_TYPE_H

namespace StructuredScript{
	class OperatorType{
	public:
		explicit OperatorType(unsigned short types)
			: types_(types){}

		bool operator <(const OperatorType &right) const{
			return (types_ < right.types_);
		}

		bool operator <=(const OperatorType &right) const{
			return (types_ <= right.types_);
		}

		bool operator ==(const OperatorType &right) const{
			return (types_ == right.types_);
		}

		bool operator !=(const OperatorType &right) const{
			return (types_ != right.types_);
		}

		bool operator >=(const OperatorType &right) const{
			return (types_ >= right.types_);
		}

		bool operator >(const OperatorType &right) const{
			return (types_ > right.types_);
		}

		bool hasType(unsigned short type, bool all = true) const{
			return all ? ((types_ & type) == type) : ((types_ & type) != 0u);
		}

		bool isLeftUnary() const{
			return ((types_ & LEFT_UNARY) == LEFT_UNARY);
		}

		bool isRightUnary() const{
			return ((types_ & RIGHT_UNARY) == RIGHT_UNARY);
		}

		bool isBinary() const{
			return ((types_ & BINARY) == BINARY);
		}

		bool isUnaryOnly() const{
			return ((types_ & BINARY) != BINARY);
		}

		bool isBinaryOnly() const{
			return (types_ == BINARY);
		}

		bool isNone() const{
			return (types_ == NONE);
		}

		unsigned short getTypes() const{
			return types_;
		}

		static const unsigned short NONE			= 0x0000;
		static const unsigned short LEFT_UNARY		= 0x0001;
		static const unsigned short RIGHT_UNARY		= 0x0002;
		static const unsigned short BINARY			= 0x0004;

		static const unsigned short UNARY			= (LEFT_UNARY | RIGHT_UNARY);

	private:
		unsigned short types_;
	};
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_TYPE_H */