#pragma once

#include "../IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class TypeResolver{
		public:
			virtual IType::Ptr resolve(IStorage *storage) = 0;
		};
	}

	typedef Interfaces::TypeResolver ITypeResolver;
}