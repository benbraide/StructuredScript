#pragma once

#ifndef STRUCTURED_SCRIPT_EXCEPTION_HANDLER_INTERFACE_H
#define STRUCTURED_SCRIPT_EXCEPTION_HANDLER_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class ExceptionHandler{
		public:
			virtual ~ExceptionHandler(){}

			virtual void finally(Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};
	}

	typedef Interfaces::ExceptionHandler IExceptionHandler;
}

#endif /* !STRUCTURED_SCRIPT_EXCEPTION_HANDLER_INTERFACE_H */