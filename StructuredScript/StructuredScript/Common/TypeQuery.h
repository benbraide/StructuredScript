#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_QUERY_H
#define STRUCTURED_SCRIPT_TYPE_QUERY_H

#include "../Interfaces/IType.h"
#include "../Interfaces/Types/IPrimitiveType.h"

namespace StructuredScript{
	namespace Query{
		class Type{
		public:
			static bool isAny(const IType *type);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_TYPE_QUERY_H */