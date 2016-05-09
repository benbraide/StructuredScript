#pragma once

#ifndef STRUCTURED_SCRIPT_EXCEPTION_MANAGER_INTERFACE_H
#define STRUCTURED_SCRIPT_EXCEPTION_MANAGER_INTERFACE_H

#include <memory>

#include "IAny.h"

namespace StructuredScript{
	namespace Interfaces{
		class ExceptionManager{
		public:
			virtual ~ExceptionManager(){}

			virtual void clear() = 0;

			virtual void set(Any::Ptr exception) = 0;

			virtual void setOnce() = 0;

			virtual void setExit() = 0;

			virtual void setReturn() = 0;

			virtual void setBreak() = 0;

			virtual void setContinue() = 0;

			virtual Any::Ptr get() const = 0;

			virtual bool has() const = 0;

			virtual bool hasOnce() const = 0;

			virtual bool hasExit() const = 0;

			virtual bool hasReturn() const = 0;

			virtual bool hasBreak() const = 0;

			virtual bool hasContinue() const = 0;
		};
	}

	typedef Interfaces::ExceptionManager IExceptionManager;
}

#endif /* !STRUCTURED_SCRIPT_EXCEPTION_MANAGER_INTERFACE_H */