#pragma once

#ifndef STRUCTURED_SCRIPT_OBJECT_QUERY_H
#define STRUCTURED_SCRIPT_OBJECT_QUERY_H

#include "../Interfaces/IAny.h"
#include "../Interfaces/Objects/IPrimitiveObject.h"
#include "../Interfaces/Objects/IFunction.h"
#include "../Interfaces/Objects/IObject.h"
#include "../Interfaces/Objects/IArray.h"
#include "../Interfaces/Storages/IFunctionStorage.h"

namespace StructuredScript{
	namespace Query{
		class Object{
		public:
			static bool isPrimitive(IAny::Ptr object);

			static bool isUndefined(IAny::Ptr object);

			static bool isExpansion(IAny::Ptr object);

			static bool isExpanded(IAny::Ptr object);

			static unsigned int getIndex(IAny::Ptr object);

			template <typename ValueType>
			static ValueType getIndexValue(IAny::Ptr object);

			template <typename TargetType, int TargetRank, typename ValueType>
			static bool getIndex(IAny::Ptr object, ValueType &value);

			static IAny *getObjectInStorage(IStorage *storage);
		};

		template <typename ValueType>
		ValueType StructuredScript::Query::Object::getIndexValue(IAny::Ptr object){
			ValueType value;

			if (getIndex<char, Objects::Primitive::CHAR_RANK, ValueType>(object, value) || getIndex<unsigned char, Objects::Primitive::UCHAR_RANK, ValueType>(object, value) ||
				getIndex<short, Objects::Primitive::SHORT_RANK, ValueType>(object, value) || getIndex<unsigned short, Objects::Primitive::USHORT_RANK, ValueType>(object, value) ||
				getIndex<int, Objects::Primitive::INT_RANK, ValueType>(object, value) || getIndex<unsigned int, Objects::Primitive::UINT_RANK, ValueType>(object, value) ||
				getIndex<long, Objects::Primitive::LONG_RANK, ValueType>(object, value) || getIndex<unsigned long, Objects::Primitive::ULONG_RANK, ValueType>(object, value) ||
				getIndex<long long, Objects::Primitive::LLONG_RANK, ValueType>(object, value) || getIndex<unsigned long long, Objects::Primitive::ULLONG_RANK, ValueType>(object, value)){
				return value;
			}

			return 0;
		}

		template <typename TargetType, int TargetRank, typename ValueType>
		bool StructuredScript::Query::Object::getIndex(IAny::Ptr object, ValueType &value){
			auto objectBase = (object == nullptr) ? nullptr : object->base();
			auto target = dynamic_cast<Objects::TypedPrimitive<TargetType, TargetRank> *>(objectBase.get());
			if (target != nullptr){
				value = static_cast<ValueType>(target->value());
				return true;
			}

			return false;
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_OBJECT_QUERY_H */