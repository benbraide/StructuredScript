#pragma once

#ifndef STRUCTURED_SCRIPT_OBJECT_INTERFACE_H
#define STRUCTURED_SCRIPT_OBJECT_INTERFACE_H

#include "IFunction.h"

namespace StructuredScript{
	namespace Interfaces{
		class Object{
		public:
			virtual ~Object(){}

			virtual void construct(const Function::ArgListType &args, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Object *findDirectParent(const std::string &name) = 0;
		};
	}

	typedef Interfaces::Object IObject;
}

#endif /* !STRUCTURED_SCRIPT_OBJECT_INTERFACE_H */