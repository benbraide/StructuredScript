#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_QUERY_H
#define STRUCTURED_SCRIPT_TYPE_QUERY_H

#include "../Interfaces/Types/IDeclaredType.h"
#include "../Interfaces/Types/ICompositeType.h"
#include "../Interfaces/Types/IPrimitiveType.h"
#include "../Interfaces/Types/IStackedType.h"

namespace StructuredScript{
	namespace Query{
		class Type{
		public:
			static bool isAny(IType::Ptr type);

			static bool isComposite(IType::Ptr type);

			static bool isStacked(IType::Ptr type);

			static bool isExpanded(IType::Ptr type);

			static bool isArray(IType::Ptr type);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_TYPE_QUERY_H */