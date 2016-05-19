#pragma once

#ifndef STRUCTURED_SCRIPT_CLASS_INTERFACE_H
#define STRUCTURED_SCRIPT_CLASS_INTERFACE_H

#include "../IAny.h"
#include "../IMemory.h"

namespace StructuredScript{
	namespace Interfaces{
		class Class{
		public:
			virtual ~Class(){}

			virtual Any::Ptr create(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Memory::Ptr constructor() = 0;

			virtual Memory::Ptr destructor() = 0;
		};
	}

	typedef Interfaces::Class IClass;
}

#endif /* !STRUCTURED_SCRIPT_CLASS_INTERFACE_H */