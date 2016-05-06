#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H
#define STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H

#include "../IMemory.h"

namespace StructuredScript{
	namespace Interfaces{
		class FunctionMemory : public Memory{
		public:
			virtual ~FunctionMemory(){}
		};
	}

	typedef Interfaces::FunctionMemory IFunctionMemory;
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H */