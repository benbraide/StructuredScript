#pragma once

#ifndef STRUCTURED_SCRIPT_INTEGER_OBJECT_H
#define STRUCTURED_SCRIPT_INTEGER_OBJECT_H

#include "Number.h"

namespace StructuredScript{
	namespace Objects{
		template <class ObjectType, class ValueType, unsigned short Rank>
		class Integer : public Number<ObjectType, ValueType, Rank>, public IInteger{
		public:
			typedef Number<ObjectType, ValueType, Rank> BaseType;

			Integer(ValueType value)
				: BaseType(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::to_string(value_);
			}

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override{
				if (value == "~")
					return std::make_shared<ObjectType>(~value_);

				if (value == "++" || value == "--")
					return step_(value[0] == '+', false, exception, expr);

				return BaseType::evaluateLeftUnary(value, exception, expr);
			}

			virtual Ptr evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr) override{
				if (value == "++" || value == "--")
					return step_(value[0] == '+', true, exception, expr);

				return BaseType::evaluateRightUnary(value, exception, expr);
			}

		protected:
			virtual IAny::Ptr evaluate_(const std::string &value, Number *left, Number *right, IExceptionManager *exception, INode *expr){
				if (value == "%"){
					if (right->value() == static_cast<ValueType>(0))
						return PrimitiveFactory::createNaN();

					return std::make_shared<ObjectType>(left->value() % right->value());
				}

				if (value == "|")
					return std::make_shared<ObjectType>(left->value() | right->value());

				if (value == "^")
					return std::make_shared<ObjectType>(left->value() ^ right->value());

				if (value == "&")
					return std::make_shared<ObjectType>(left->value() & right->value());

				if (value == "<<")
					return std::make_shared<ObjectType>(left->value() << right->value());

				if (value == ">>")
					return std::make_shared<ObjectType>(left->value() >> right->value());

				return BaseType::evaluate_(value, left, right, exception, expr);
			}

			Ptr step_(bool forward, bool post, IExceptionManager *exception, INode *expr){
				if (memory_ == nullptr)
					return nullptr;//TODO: Throw exception

				Ptr copy;
				if (post)
					copy = std::make_shared<ObjectType>(value_);

				if (forward)
					++value_;
				else
					--value_;

				return post ? copy : ptr();
			}
		};

		template <class ObjectType, class ValueType, unsigned short Rank>
		class SignedInteger : public Integer<ObjectType, ValueType, Rank> {
		public:
			typedef Integer<ObjectType, ValueType, Rank> BaseType;

			SignedInteger(ValueType value)
				: BaseType(value){}

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override{
				if (value == "+")
					return std::make_shared<ObjectType>(value_);

				if (value == "-")
					return std::make_shared<ObjectType>(-value_);

				return BaseType::evaluateLeftUnary(value, exception, expr);
			}
		};

		class Char : public SignedInteger<Char, char, Primitive::CHAR_RANK> {
		public:
			Char(char value)
				: SignedInteger(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::string(1, value_);
			}
		};

		class UChar : public Integer<UChar, unsigned char, Primitive::UCHAR_RANK> {
		public:
			UChar(unsigned char value)
				: Integer(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::string(1, static_cast<char>(value_));
			}
		};

		class Short : public SignedInteger<Short, short, Primitive::SHORT_RANK> {
		public:
			Short(short value)
				: SignedInteger(value){}
		};

		class UShort : public Integer<UShort, unsigned short, Primitive::USHORT_RANK> {
		public:
			UShort(unsigned short value)
				: Integer(value){}
		};

		class Int : public SignedInteger<Int, int, Primitive::INT_RANK> {
		public:
			Int(int value)
				: SignedInteger(value){}
		};

		class UInt : public Integer<UInt, unsigned int, Primitive::UINT_RANK> {
		public:
			UInt(unsigned int value)
				: Integer(value){}
		};

		class Long : public SignedInteger<Long, long, Primitive::LONG_RANK> {
		public:
			Long(long value)
				: SignedInteger(value){}
		};

		class ULong : public Integer<ULong, unsigned long, Primitive::ULONG_RANK> {
		public:
			ULong(unsigned long value)
				: Integer(value){}
		};

		class LLong : public SignedInteger<LLong, long long, Primitive::LLONG_RANK> {
		public:
			LLong(long long value)
				: SignedInteger(value){}
		};

		class ULLong : public Integer<ULLong, unsigned long long, Primitive::ULLONG_RANK> {
		public:
			ULLong(unsigned long long value)
				: Integer(value){}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_INTEGER_OBJECT_H */