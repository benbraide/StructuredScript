#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H
#define STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H

#include "../IMemory.h"
#include "../Objects/IFunction.h"

namespace StructuredScript{
	namespace Interfaces{
		class FunctionMemory{
		public:
			virtual ~FunctionMemory(){}

			virtual Memory::Ptr add(Any::Ptr function, MemoryAttributes::Ptr attributes) = 0;

			virtual Memory::Ptr find(const Function::ArgListType &args) = 0;

			virtual Memory::Ptr find(const Function::TypeListType &args) = 0;
		};
	}

	typedef Interfaces::FunctionMemory IFunctionMemory;
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H */