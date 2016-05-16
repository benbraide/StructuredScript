#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_BACKDOOR_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_BACKDOOR_INTERFACE_H

#include "../IMemory.h"

namespace StructuredScript{
	namespace Interfaces{
		class MemoryBackdoor{
		public:
			virtual ~MemoryBackdoor(){}

			virtual void assign(Any::Ptr object) = 0;
		};
	}

	typedef Interfaces::MemoryBackdoor IMemoryBackdoor;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_BACKDOOR_INTERFACE_H */