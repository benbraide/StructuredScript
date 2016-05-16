#pragma once

#ifndef STRUCTURED_SCRIPT_OBJECT_QUERY_H
#define STRUCTURED_SCRIPT_OBJECT_QUERY_H

#include "../Interfaces/IAny.h"
#include "../Interfaces/Objects/IPrimitiveObject.h"
#include "../Interfaces/Objects/IFunction.h"

namespace StructuredScript{
	namespace Query{
		class Object{
		public:
			static bool isPrimitive(IAny::Ptr object);

			static bool isUndefined(IAny::Ptr object);

			static unsigned int getIndex(IAny::Ptr object);

			template <typename TargetType, int TargetRank>
			static bool getIndex(IAny::Ptr object, unsigned int &value);

			static IAny::Ptr getObjectInStorage(IStorage *storage);
		};

		template <typename TargetType, int TargetRank>
		bool StructuredScript::Query::Object::getIndex(IAny::Ptr object, unsigned int &value){
			auto objectBase = object->base();
			auto target = dynamic_cast<Objects::TypedPrimitive<TargetType, TargetRank> *>(objectBase.get());
			if (target != nullptr){
				value = static_cast<unsigned int>(target->value());
				return true;
			}

			return false;
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_OBJECT_QUERY_H */