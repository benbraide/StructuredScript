#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_RESOLVER_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_RESOLVER_INTERFACE_H

#include "../IMemory.h"

namespace StructuredScript{
	namespace Interfaces{
		class MemoryResolver{
		public:
			virtual ~MemoryResolver(){}

			virtual Memory::Ptr resolveMemory(Storage *storage, unsigned short searchScope = Storage::SEARCH_DEFAULT) = 0;
		};
	}

	typedef Interfaces::MemoryResolver IMemoryResolver;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_RESOLVER_INTERFACE_H */