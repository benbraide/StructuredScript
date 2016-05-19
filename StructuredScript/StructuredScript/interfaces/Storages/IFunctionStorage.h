#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_STORAGE_INTERFACE_H
#define STRUCTURED_SCRIPT_FUNCTION_STORAGE_INTERFACE_H

#include "../IAny.h"

namespace StructuredScript{
	namespace Interfaces{
		class FunctionStorage{
		public:
			virtual ~FunctionStorage(){}

			virtual Any::Ptr object() = 0;
		};
	}

	typedef Interfaces::FunctionStorage IFunctionStorage;
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_STORAGE_INTERFACE_H */