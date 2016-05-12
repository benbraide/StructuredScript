#pragma once

#ifndef STRUCTURED_SCRIPT_OBJECT_QUERY_H
#define STRUCTURED_SCRIPT_OBJECT_QUERY_H

#include "../Interfaces/IAny.h"
#include "../Interfaces/Objects/IPrimitiveObject.h"

namespace StructuredScript{
	namespace Query{
		class Object{
		public:
			static bool isPrimitive(IAny::Ptr object);

			static bool isUndefined(IAny::Ptr object);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_OBJECT_QUERY_H */