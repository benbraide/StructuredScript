#pragma once

#ifndef STRUCTURED_SCRIPT_GLOBAL_STORAGE_INTERFACE_H
#define STRUCTURED_SCRIPT_GLOBAL_STORAGE_INTERFACE_H

#include "../../Common/Typename.h"

namespace StructuredScript{
	namespace Interfaces{
		class GlobalStorage{
		public:
			virtual Type::Ptr getPrimitiveType(Typename type) = 0;

			virtual Type::Ptr getPrimitiveType(int rank) = 0;

			static GlobalStorage *globalStorage;
		};
	}

	typedef Interfaces::GlobalStorage IGlobalStorage;
}

#endif /* !STRUCTURED_SCRIPT_GLOBAL_STORAGE_INTERFACE_H */