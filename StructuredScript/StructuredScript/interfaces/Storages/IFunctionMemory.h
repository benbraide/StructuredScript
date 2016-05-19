#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H
#define STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H

#include "../INode.h"
#include "../Objects/IFunction.h"

namespace StructuredScript{
	namespace Interfaces{
		class FunctionMemory{
		public:
			virtual ~FunctionMemory(){}

			virtual void setStorage(Storage *storage) = 0;

			virtual Memory::Ptr add(Any::Ptr function, MemoryAttributes::Ptr attributes) = 0;

			virtual bool remove(Memory::Ptr function) = 0;

			virtual Any::Ptr call(bool rightUnary, const Function::ArgListType &args, ExceptionManager *exception, Node *expr) = 0;

			virtual Memory::Ptr find(bool rightUnary, Any::Ptr object, const Function::ArgListType &args) = 0;

			virtual Memory::Ptr find(bool rightUnary, Any::Ptr object, const Function::TypeListType &args) = 0;

			virtual Memory::Ptr first() = 0;

			virtual Memory::Ptr filterNonMembers() = 0;

			virtual void resolveArgs(Node::Ptr args, Function::ArgListType &resolved, Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};
	}

	typedef Interfaces::FunctionMemory IFunctionMemory;
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_MEMORY_INTERFACE_H */