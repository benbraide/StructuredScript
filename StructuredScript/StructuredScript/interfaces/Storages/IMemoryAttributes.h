#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_ATTRIBUTES_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_ATTRIBUTES_INTERFACE_H


#include <string>

#include "IMemoryAttribute.h"

namespace StructuredScript{
	namespace Interfaces{
		class MemoryAttributes : protected std::enable_shared_from_this<MemoryAttributes>{
		public:
			typedef std::shared_ptr<MemoryAttributes> Ptr;

			virtual Ptr ptr() = 0;

			virtual MemoryAttribute::Ptr getAttribute(const std::string &name) = 0;

			virtual bool hasAttribute(const std::string &name) const = 0;

			virtual std::string str() const = 0;
		};
	}

	typedef Interfaces::MemoryAttributes IMemoryAttributes;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_ATTRIBUTES_INTERFACE_H */