#pragma once

#ifndef STRUCTURED_SCRIPT_TYPED_PRIMITIVE_OBJECT_H
#define STRUCTURED_SCRIPT_TYPED_PRIMITIVE_OBJECT_H

#include "Primitive.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		template <class ValueType, int Rank>
		class TypedPrimitive : public Primitive, public IIndexTarget{
		public:
			explicit TypedPrimitive(const ValueType &value)
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Rank)), value_(value){}

			TypedPrimitive(IType::Ptr type, const ValueType &value)
				: Primitive(type), value_(value){}

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return (value_ != static_cast<std::remove_reference<ValueType>::type>(0));
			}

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override{
				if (value != "[]")
					return Primitive::evaluateBinary(value, right, storage, exception, expr);

				if (dynamic_cast<IInteger *>(right->base()) == nullptr){
					return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
						"'[]': Expected index to be an integral value!", expr)));
				}

				auto index = getIndex(right);
				if (index >= sizeof value_){
					return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
						"'[]': Index is out of bounds!", expr)));
				}

				if (memory_ == nullptr)
					return PrimitiveFactory::createByte(reinterpret_cast<unsigned char *>(&value_)[index]);

				return PrimitiveFactory::createIndexObject(type_, index, memory_);
			}

			virtual int rank() override{
				return Rank;
			}

			virtual Ptr getIndexValue(unsigned int index) override{
				return PrimitiveFactory::createByte(reinterpret_cast<unsigned char *>(&value_)[index]);
			}

			void setValue(const ValueType &value){
				value_ = value;
			}

			ValueType value(){
				return value_;
			}

			static unsigned int getIndex(Ptr target){
				unsigned int value;

				if (getIndex<char, CHAR_RANK>(target, value) || getIndex<unsigned char, UCHAR_RANK>(target, value) ||
					getIndex<short, SHORT_RANK>(target, value) || getIndex<unsigned short, USHORT_RANK>(target, value) ||
					getIndex<int, INT_RANK>(target, value) || getIndex<unsigned int, UINT_RANK>(target, value) ||
					getIndex<long, LONG_RANK>(target, value) || getIndex<unsigned long, ULONG_RANK>(target, value) ||
					getIndex<long long, LLONG_RANK>(target, value) || getIndex<unsigned long long, ULLONG_RANK>(target, value)){
					return value;
				}

				return 0;
			}

			template <typename TargetType, int TargetRank>
			static bool getIndex(Ptr target, unsigned int &value){
				auto object = dynamic_cast<TypedPrimitive<TargetType, TargetRank> *>(target->base());
				if (object != nullptr){
					value = static_cast<unsigned int>(object->value());
					return true;
				}

				return false;
			}

		protected:
			virtual Ptr promote_(Primitive *target) override{
				return nullptr;
			}

			virtual IAny::Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override{
				auto primitive = (right == nullptr) ? nullptr : dynamic_cast<TypedPrimitive *>(right->base());
				if (primitive == nullptr){
					return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
						"'" + value + "': Operands mismatch!", expr)));
				}

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

				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
					"'" + value + "': Operands mismatch!", expr)));
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