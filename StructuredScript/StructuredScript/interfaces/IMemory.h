#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_INTERFACE_H

#include "../Common/Typename.h"

#include "IType.h"
#include "IExceptionManager.h"

namespace StructuredScript{
	namespace Interfaces{
		class Memory{
		public:
			typedef std::shared_ptr<Any> AnyPtr;

			virtual ~Memory(){}

			virtual void setObject(AnyPtr object, ExceptionManager *exception, Node *expr) = 0;

			virtual AnyPtr getObject() = 0;

			virtual DeclaredType *getType() = 0;

			virtual Storage *getStorage() = 0;
		};
	}

	typedef Interfaces::Memory IMemory;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_INTERFACE_H */