#pragma once

#ifndef STRUCTURED_SCRIPT_INTEGER_OBJECT_H
#define STRUCTURED_SCRIPT_INTEGER_OBJECT_H

#include "Number.h"

namespace StructuredScript{
	namespace Objects{
		template <class ObjectType, class ValueType, unsigned short Rank>
		class Integer : public Number<ObjectType, ValueType, Rank>, public IInteger{
		public:
			typedef Number<ObjectType, ValueType, Rank>	BaseType;
			typedef TypedPrimitive<ValueType, Rank>		BaseType_;

			explicit Integer(ValueType value)
				: BaseType(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::to_string(value_);
			}

			virtual Ptr evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr) override{
				if (value == "~")
					return std::make_shared<ObjectType>(~value_);

				if (value == "++" || value == "--")
					return step_(value[0] == '+', false, exception, expr);

				return BaseType::evaluateLeftUnary(value, storage, exception, expr);
			}

			virtual Ptr evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr) override{
				if (value == "++" || value == "--")
					return step_(value[0] == '+', true, exception, expr);

				return BaseType::evaluateRightUnary(value, storage, exception, expr);
			}

		protected:
			virtual IAny::Ptr evaluate_(const std::string &value, BaseType_ *left, BaseType_ *right, IExceptionManager *exception, INode *expr) override{
				if (value == "**")
					return PrimitiveFactory::createDouble(std::pow(left->value(), right->value()));

				if (value == "%"){
					if (right->value() == static_cast<std::remove_reference<ValueType>::type>(0))
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
		class SignedInteger : public Integer<ObjectType, ValueType, Rank>, public ISignedInteger{
		public:
			typedef Integer<ObjectType, ValueType, Rank> BaseType;

			explicit SignedInteger(ValueType value)
				: BaseType(value){}

			virtual Ptr evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr) override{
				if (value == "+")
					return std::make_shared<ObjectType>(value_);

				if (value == "-")
					return std::make_shared<ObjectType>(-value_);

				return BaseType::evaluateLeftUnary(value, storage, exception, expr);
			}
		};

		class Char : public SignedInteger<Char, char, Primitive::CHAR_RANK> {
		public:
			explicit Char(char value)
				: SignedInteger(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::string(1, value_);
			}
		};

		class UChar : public Integer<UChar, unsigned char, Primitive::UCHAR_RANK> {
		public:
			explicit UChar(unsigned char value)
				: Integer(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::string(1, static_cast<char>(value_));
			}
		};

		class LChar : public SignedInteger<Char, char &, Primitive::CHAR_RANK> {
		public:
			explicit LChar(char &value)
				: SignedInteger(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::string(1, value_);
			}

			virtual Ptr assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override{
				if (value.size() > 1u){//Compound assignment
					right = Primitive::evaluateBinary(value.substr(0, value.size() - 1), right, storage, exception, expr);
					if (Query::ExceptionManager::has(exception))
						return nullptr;
				}

				auto rightBase = right->base();
				right = promote_(dynamic_cast<Primitive *>(rightBase.get()));
				if (right == nullptr){
					return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
						"'" + value + "': Operands mismatch!", expr)));
				}

				value_ = dynamic_cast<Char *>(rightBase.get())->value();
				return ptr();
			}

		protected:
			virtual Ptr prepForExpression_() override{
				return std::make_shared<Char>(value_);
			}
		};

		class Short : public SignedInteger<Short, short, Primitive::SHORT_RANK> {
		public:
			explicit Short(short value)
				: SignedInteger(value){}
		};

		class UShort : public Integer<UShort, unsigned short, Primitive::USHORT_RANK> {
		public:
			explicit UShort(unsigned short value)
				: Integer(value){}
		};

		class Int : public SignedInteger<Int, int, Primitive::INT_RANK> {
		public:
			explicit Int(int value)
				: SignedInteger(value){}
		};

		class UInt : public Integer<UInt, unsigned int, Primitive::UINT_RANK> {
		public:
			explicit UInt(unsigned int value)
				: Integer(value){}
		};

		class Long : public SignedInteger<Long, long, Primitive::LONG_RANK> {
		public:
			explicit Long(long value)
				: SignedInteger(value){}
		};

		class ULong : public Integer<ULong, unsigned long, Primitive::ULONG_RANK> {
		public:
			explicit ULong(unsigned long value)
				: Integer(value){}
		};

		class LLong : public SignedInteger<LLong, long long, Primitive::LLONG_RANK> {
		public:
			explicit LLong(long long value)
				: SignedInteger(value){}
		};

		class ULLong : public Integer<ULLong, unsigned long long, Primitive::ULLONG_RANK> {
		public:
			explicit ULLong(unsigned long long value)
				: Integer(value){}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_INTEGER_OBJECT_H */