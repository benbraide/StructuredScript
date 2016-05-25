#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_ADDER_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_ADDER_INTERFACE_H

#include "../IMemory.h"

namespace StructuredScript{
	namespace Interfaces{
		class MemoryAdder{
		public:
			virtual ~MemoryAdder(){}

			virtual Storage::MemoryInfo *addMemory(Storage *storage) = 0;

			virtual Storage::MemoryInfo *addNonOperatorMemory(Storage *storage) = 0;
		};
	}

	typedef Interfaces::MemoryAdder IMemoryAdder;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_ADDER_INTERFACE_H */