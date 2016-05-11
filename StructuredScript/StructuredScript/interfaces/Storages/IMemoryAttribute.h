#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_ATTRIBUTE_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_ATTRIBUTE_INTERFACE_H

#include "../IExceptionManager.h"

namespace StructuredScript{
	namespace Interfaces{
		class Memory;

		class MemoryAttribute : protected std::enable_shared_from_this<MemoryAttribute>{
		public:
			typedef std::shared_ptr<MemoryAttribute> Ptr;

			virtual ~MemoryAttribute(){}

			virtual Ptr ptr() = 0;

			virtual bool appliesTo(Memory *memory, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual bool appliesTo(Node *node, Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};
	}

	typedef Interfaces::MemoryAttribute IMemoryAttribute;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_ATTRIBUTE_INTERFACE_H */