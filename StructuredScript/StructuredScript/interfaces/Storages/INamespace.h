#pragma once

#ifndef STRUCTURED_SCRIPT_NAMESPACE_INTERFACE_H
#define STRUCTURED_SCRIPT_NAMESPACE_INTERFACE_H

#include "../IStorage.h"

namespace StructuredScript{
	namespace Interfaces{
		class Namespace{
		public:
			virtual ~Namespace(){}

			virtual std::string name() const = 0;
		};
	}

	typedef Interfaces::Namespace INamespace;
}

#endif /* !STRUCTURED_SCRIPT_NAMESPACE_INTERFACE_H */