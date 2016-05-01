#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_INTERFACE_H
#define STRUCTURED_SCRIPT_STORAGE_INTERFACE_H

#include <string>

namespace StructuredScript{
	namespace Interfaces{
		class Memory;

		class Storage{
		public:
			virtual ~Storage(){}

			virtual Storage *addStorage(const std::string &name) = 0;

			virtual Storage *findStorage(const std::string &name, bool localOnly) = 0;

			virtual Memory *addMemory(const std::string &name) = 0;

			virtual Memory *findMemory(const std::string &name, bool localOnly) = 0;

			virtual bool remove(const Memory *target) = 0;
		};
	}

	typedef Interfaces::Storage IStorage;
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_INTERFACE_H */