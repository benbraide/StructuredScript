#pragma once

#ifndef STRUCTURED_SCRIPT_NUMBER_OBJECT_H
#define STRUCTURED_SCRIPT_NUMBER_OBJECT_H

#include <cmath>

#include "TypedPrimitive.h"

namespace StructuredScript{
	namespace Objects{
		template <class ObjectType, class ValueType, unsigned short Rank>
		class Number : public TypedPrimitive<ValueType, Rank>, public INumber{
		public:
			typedef TypedPrimitive<ValueType, Rank> BaseType;

			explicit Number(ValueType value)
				: BaseType(value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::make_shared<ObjectType>(value_);
			}

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override{
				if (type->isEqual(BaseType::type_))
					return ptr();

				auto primitive = dynamic_cast<IPrimitiveType *>(type.get());
				if (primitive == nullptr)
					return nullptr;

				switch (primitive->value()){
				case Typename::TYPE_NAME_CHAR:
					return PrimitiveFactory::createChar(static_cast<char>(value_));
				case Typename::TYPE_NAME_UCHAR:
					return PrimitiveFactory::createUChar(static_cast<unsigned char>(value_));
				case Typename::TYPE_NAME_SHORT:
					return PrimitiveFactory::createShort(static_cast<short>(value_));
				case Typename::TYPE_NAME_USHORT:
					return PrimitiveFactory::createUShort(static_cast<unsigned short>(value_));
				case Typename::TYPE_NAME_INT:
					return PrimitiveFactory::createInt(static_cast<int>(value_));
				case Typename::TYPE_NAME_UINT:
					return PrimitiveFactory::createUInt(static_cast<unsigned int>(value_));
				case Typename::TYPE_NAME_LONG:
					return PrimitiveFactory::createLong(static_cast<long>(value_));
				case Typename::TYPE_NAME_ULONG:
					return PrimitiveFactory::createULong(static_cast<unsigned long>(value_));
				case Typename::TYPE_NAME_LLONG:
					return PrimitiveFactory::createLLong(static_cast<long long>(value_));
				case Typename::TYPE_NAME_ULLONG:
					return PrimitiveFactory::createULLong(static_cast<unsigned long long>(value_));
				case Typename::TYPE_NAME_FLOAT:
					return PrimitiveFactory::createFloat(static_cast<float>(value_));
				case Typename::TYPE_NAME_DOUBLE:
					return PrimitiveFactory::createDouble(static_cast<double>(value_));
				case Typename::TYPE_NAME_LDOUBLE:
					return PrimitiveFactory::createLDouble(static_cast<long double>(value_));
				case Typename::TYPE_NAME_STRING:
					return PrimitiveFactory::createString(str(nullptr, nullptr, nullptr));
				default:
					break;
				}

				return nullptr;
			}

			virtual unsigned int size() const override{
				return sizeof(value_);
			}

		protected:
			virtual IAny::Ptr promote_(Primitive *target) override{
				if (dynamic_cast<Number *>(target) != nullptr)//Same type
					return target->ptr();

				switch (target->rank()){
				case Primitive::CHAR_RANK:
					return promoteChar_(target);
				case Primitive::UCHAR_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::UCHAR_RANK>::type *>(target)->value()));
				case Primitive::SHORT_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::SHORT_RANK>::type *>(target)->value()));
				case Primitive::USHORT_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::USHORT_RANK>::type *>(target)->value()));
				case Primitive::INT_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::INT_RANK>::type *>(target)->value()));
				case Primitive::UINT_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::UINT_RANK>::type *>(target)->value()));
				case Primitive::LONG_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::LONG_RANK>::type *>(target)->value()));
				case Primitive::ULONG_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::ULONG_RANK>::type *>(target)->value()));
				case Primitive::LLONG_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::LLONG_RANK>::type *>(target)->value()));
				case Primitive::ULLONG_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::ULLONG_RANK>::type *>(target)->value()));
				case Primitive::FLOAT_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::FLOAT_RANK>::type *>(target)->value()));
				case Primitive::DOUBLE_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::DOUBLE_RANK>::type *>(target)->value()));
				case Primitive::LDOUBLE_RANK:
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(dynamic_cast<PrimitiveType<Primitive::LDOUBLE_RANK>::type *>(target)->value()));
				default:
					break;
				}

				return nullptr;
			}

			virtual IAny::Ptr evaluate_(const std::string &value, BaseType *left, BaseType *right, IExceptionManager *exception, INode *expr) override{
				if (value == "+")
					return std::make_shared<ObjectType>(left->value() + right->value());

				if (value == "-")
					return std::make_shared<ObjectType>(left->value() - right->value());

				if (value == "*")
					return std::make_shared<ObjectType>(left->value() * right->value());

				if (value == "/"){
					if (right->value() == static_cast<std::remove_reference<ValueType>::type>(0))
						return PrimitiveFactory::createNaN();

					return std::make_shared<ObjectType>(left->value() / right->value());
				}

				return BaseType::evaluate_(value, left, right, exception, expr);
			}

			IAny::Ptr promoteChar_(Primitive *target){
				auto object = dynamic_cast<PrimitiveType<Primitive::CHAR_RANK>::type *>(target);
				if (object != nullptr)
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(object->value()));

				auto lchar = dynamic_cast<TypedPrimitive<char &, Primitive::CHAR_RANK> *>(target);
				if (lchar != nullptr)
					return std::make_shared<ObjectType>(static_cast<std::remove_reference<ValueType>::type>(lchar->value()));

				return nullptr;
			}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NUMBER_OBJECT_H */