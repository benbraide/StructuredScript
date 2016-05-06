#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_INTERFACE_H

#include "../Common/DeclaredType.h"

#include "IType.h"
#include "IExceptionManager.h"

namespace StructuredScript{
	namespace Interfaces{
		class Memory : protected std::enable_shared_from_this<Memory>{
		public:
			typedef std::shared_ptr<Memory> Ptr;

			virtual ~Memory(){}

			virtual Ptr ptr() = 0;

			virtual void assign(IAny::Ptr object, ExceptionManager *exception, Node *expr) = 0;

			virtual IAny::Ptr object() = 0;

			virtual DeclaredType *type() = 0;

			virtual Storage *storage() = 0;
		};
	}

	typedef Interfaces::Memory IMemory;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_INTERFACE_H */