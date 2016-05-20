#pragma once

#ifndef STRUCTURED_SCRIPT_CLASS_ENTRY_INTERFACE_H
#define STRUCTURED_SCRIPT_CLASS_ENTRY_INTERFACE_H

#include <string>

namespace StructuredScript{
	namespace Interfaces{
		class ClassEntry{
		public:
			virtual ~ClassEntry(){}

			virtual std::string declName() = 0;
		};
	}

	typedef Interfaces::ClassEntry IClassEntry;
}

#endif /* !STRUCTURED_SCRIPT_CLASS_ENTRY_INTERFACE_H */