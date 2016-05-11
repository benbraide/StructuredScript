#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_ATTRIBUTES_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_ATTRIBUTES_INTERFACE_H

#include <map>
#include <string>

#include "IMemoryAttribute.h"

namespace StructuredScript{
	namespace Interfaces{
		class MemoryAttributes{
		public:
			typedef std::map<std::string, MemoryAttribute::Ptr> ListType;

			virtual MemoryAttribute::Ptr getAttribute(const std::string &name) = 0;

			virtual bool hasAttribute(const std::string &name) const = 0;

		private:
			ListType attributes_;
		};
	}

	typedef Interfaces::MemoryAttributes IMemoryAttributes;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_ATTRIBUTES_INTERFACE_H */