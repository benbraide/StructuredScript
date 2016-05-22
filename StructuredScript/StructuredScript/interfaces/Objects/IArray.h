#pragma once

#ifndef STRUCTURED_SCRIPT_ARRAY_OBJECT_INTERFACE_H
#define STRUCTURED_SCRIPT_ARRAY_OBJECT_INTERFACE_H

#include <vector>

#include "../IAny.h"
#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class ArrayObject{
		public:
			typedef std::vector<Memory::Ptr> MemoryListType;

			virtual ~ArrayObject(){}

			virtual Any::Ptr at(unsigned int index) = 0;

			virtual void append(Any::Ptr value, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual void insert(unsigned int index, Any::Ptr value, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual void insert(MemoryListType::iterator index, Any::Ptr value, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual void erase(unsigned int index) = 0;

			virtual void erase(MemoryListType::iterator index) = 0;

			virtual void clear() = 0;

			virtual bool empty() = 0;

			virtual void size(unsigned int value) = 0;

			virtual unsigned int size() = 0;

			virtual const MemoryListType &list() const = 0;
		};
	}

	typedef Interfaces::ArrayObject IArrayObject;
}

#endif /* !STRUCTURED_SCRIPT_ARRAY_OBJECT_INTERFACE_H */