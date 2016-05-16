#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_RESOLVER_INTERFACE_H
#define STRUCTURED_SCRIPT_TYPE_RESOLVER_INTERFACE_H

#include "../IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class TypeResolver{
		public:
			virtual ~TypeResolver(){}

			virtual Type::Ptr resolveType(Storage *storage, unsigned short searchScope = Storage::SEARCH_DEFAULT) = 0;
		};
	}

	typedef Interfaces::TypeResolver ITypeResolver;
}

#endif /* !STRUCTURED_SCRIPT_TYPE_RESOLVER_INTERFACE_H */