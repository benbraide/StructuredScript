#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_ADDER_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_ADDER_INTERFACE_H

#include "../IMemory.h"

namespace StructuredScript{
	namespace Interfaces{
		class MemoryAdder{
		public:
			virtual ~MemoryAdder(){}

			virtual Memory::Ptr *addMemory(Storage *storage) = 0;

			virtual Memory::Ptr *addNonOperatorMemory(Storage *storage) = 0;
		};
	}

	typedef Interfaces::MemoryAdder IMemoryAdder;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_ADDER_INTERFACE_H */