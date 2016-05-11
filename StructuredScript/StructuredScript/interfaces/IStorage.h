#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_INTERFACE_H
#define STRUCTURED_SCRIPT_STORAGE_INTERFACE_H

#include <string>
#include <memory>

namespace StructuredScript{
	namespace Interfaces{
		class Type;
		class Node;
		class Memory;
		class MemoryAttribute;

		class Storage{
		public:
			virtual ~Storage(){}

			virtual std::shared_ptr<Storage> *addStorage(const std::string &name) = 0;

			virtual Storage *findStorage(const std::string &name, bool localOnly) = 0;

			virtual std::shared_ptr<Type> *addType(const std::string &name) = 0;

			virtual std::shared_ptr<Type> findType(const std::string &name, bool localOnly) = 0;

			virtual std::shared_ptr<Memory> *addMemory(const std::string &name) = 0;

			virtual std::shared_ptr<Memory> findMemory(const std::string &name, bool localOnly) = 0;

			virtual std::shared_ptr<Memory> *addOperatorMemory(const std::string &name) = 0;

			virtual std::shared_ptr<Memory> findOperatorMemory(const std::string &name, bool localOnly) = 0;

			virtual std::shared_ptr<Memory> *addTypenameOperatorMemory(const std::string &name) = 0;

			virtual std::shared_ptr<Memory> findTypenameOperatorMemory(const std::string &name, bool localOnly) = 0;

			virtual std::shared_ptr<MemoryAttribute> *addMemoryAttribute(const std::string &name) = 0;

			virtual std::shared_ptr<MemoryAttribute> findMemoryAttribute(const std::string &name, bool localOnly) = 0;

			virtual bool remove(const Memory *target) = 0;
		};
	}

	typedef Interfaces::Storage IStorage;
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_INTERFACE_H */