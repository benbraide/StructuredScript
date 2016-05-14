#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_RESOLVER_INTERFACE_H
#define STRUCTURED_SCRIPT_STORAGE_RESOLVER_INTERFACE_H

#include "../IStorage.h"

namespace StructuredScript{
	namespace Interfaces{
		class StorageResolver{
		public:
			virtual ~StorageResolver(){}

			virtual Storage *resolveStorage(Storage *storage) = 0;
		};
	}

	typedef Interfaces::StorageResolver IStorageResolver;
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_RESOLVER_INTERFACE_H */