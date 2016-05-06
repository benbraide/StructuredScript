#pragma once

#ifndef STRUCTURED_SCRIPT_TYPED_PRIMITIVE_OBJECT_H
#define STRUCTURED_SCRIPT_TYPED_PRIMITIVE_OBJECT_H

#include "Primitive.h"

#include "../Common/Factory.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		template <class ValueType, int Rank>
		class TypedPrimitive : public Primitive{
		public:
			TypedPrimitive(const ValueType &value)
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Rank)), value_(value){}

			TypedPrimitive(IType::Ptr type, const ValueType &value)
				: Primitive(type), value_(value){}

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return (value_ != static_cast<ValueType>(0));
			}

			virtual int rank() override{
				return Rank;
			}

			void setValue(const ValueType &value){
				value_ = value;
			}

			ValueType value(){
				return value_;
			}

		protected:
			virtual Ptr promote_(Primitive *target) override{
				return nullptr;
			}

			virtual IAny::Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override{
				auto primitive = dynamic_cast<TypedPrimitive *>(right.get());
				if (primitive == nullptr)
					return nullptr;//TODO: Throw exception

				return reversed ? evaluate_(value, primitive, this, exception, expr) : evaluate_(value, this, primitive, exception, expr);
			}

			virtual IAny::Ptr evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr){
				if (value == "<")
					return PrimitiveFactory::createBool(left->value_ < right->value_);

				if (value == "<=")
					return PrimitiveFactory::createBool(left->value_ <= right->value_);

				if (value == "==")
					return PrimitiveFactory::createBool(left->value_ == right->value_);

				if (value == "!=")
					return PrimitiveFactory::createBool(left->value_ != right->value_);

				if (value == ">=")
					return PrimitiveFactory::createBool(left->value_ >= right->value_);

				if (value == ">")
					return PrimitiveFactory::createBool(left->value_ > right->value_);

				return nullptr;
			}

			ValueType value_;
		};

		template <int Rank>
		struct PrimitiveType{
			typedef TypedPrimitive<char, Primitive::CHAR_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::CHAR_RANK>{
			typedef TypedPrimitive<char, Primitive::CHAR_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::UCHAR_RANK>{
			typedef TypedPrimitive<unsigned char, Primitive::UCHAR_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::SHORT_RANK>{
			typedef TypedPrimitive<short, Primitive::SHORT_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::USHORT_RANK>{
			typedef TypedPrimitive<unsigned short, Primitive::USHORT_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::INT_RANK>{
			typedef TypedPrimitive<int, Primitive::INT_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::UINT_RANK>{
			typedef TypedPrimitive<unsigned int, Primitive::UINT_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::LONG_RANK>{
			typedef TypedPrimitive<long, Primitive::LONG_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::ULONG_RANK>{
			typedef TypedPrimitive<unsigned long, Primitive::ULONG_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::LLONG_RANK>{
			typedef TypedPrimitive<long long, Primitive::LLONG_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::ULLONG_RANK>{
			typedef TypedPrimitive<unsigned long long, Primitive::ULLONG_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::FLOAT_RANK>{
			typedef TypedPrimitive<float, Primitive::FLOAT_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::DOUBLE_RANK>{
			typedef TypedPrimitive<double, Primitive::DOUBLE_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::LDOUBLE_RANK>{
			typedef TypedPrimitive<long double, Primitive::LDOUBLE_RANK> type;
		};

		template <>
		struct PrimitiveType<Primitive::STRING_RANK>{
			typedef TypedPrimitive<std::string, Primitive::STRING_RANK> type;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_TYPED_PRIMITIVE_OBJECT_H */