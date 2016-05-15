#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_INTERFACE_H
#define STRUCTURED_SCRIPT_STORAGE_INTERFACE_H

#include <list>
#include <string>
#include <memory>
#include <functional>

namespace StructuredScript{
	namespace Interfaces{
		class Any;
		class Type;
		class Node;
		class Memory;
		class MemoryAttribute;
		class ExceptionManager;

		class Storage{
		public:
			typedef std::shared_ptr<Any> AnyPtr;
			typedef std::function<AnyPtr(Storage *storage, ExceptionManager *exception, Node *expr)> ExternalCallType;

			virtual ~Storage(){}

			virtual Storage *parent() = 0;

			virtual std::shared_ptr<Storage> *addStorage(const std::string &name) = 0;

			virtual Storage *findStorage(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Type> *addType(const std::string &name) = 0;

			virtual std::shared_ptr<Type> findType(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Memory> *addMemory(const std::string &name) = 0;

			virtual std::shared_ptr<Memory> findMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Memory> findFunctionMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Memory> *addOperatorMemory(const std::string &name) = 0;

			virtual std::shared_ptr<Memory> findOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Memory> *addTypenameOperatorMemory(const std::string &name) = 0;

			virtual std::shared_ptr<Memory> findTypenameOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<MemoryAttribute> *addMemoryAttribute(const std::string &name) = 0;

			virtual std::shared_ptr<MemoryAttribute> findMemoryAttribute(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) = 0;

			virtual ExternalCallType findExternalCall(const std::string &name) = 0;

			virtual bool remove(std::shared_ptr<Memory> target) = 0;

			static const unsigned short SEARCH_DEFAULT		= 0x0000;
			static const unsigned short SEARCH_FAMILY		= 0x0001;
			static const unsigned short SEARCH_LOCAL		= 0x0002;
		};
	}

	typedef Interfaces::Storage IStorage;
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_INTERFACE_H */