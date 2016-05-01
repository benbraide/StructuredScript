#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_INTERFACE_H
#define STRUCTURED_SCRIPT_TYPE_INTERFACE_H

#include "IStorage.h"

namespace StructuredScript{
	namespace Interfaces{
		class Type{
		public:
			virtual ~Type(){}

			virtual Storage *getStorage() = 0;

			virtual bool isCompatibleWith(const Type &target) const = 0;

			virtual bool isPartOf(const std::string &group) const = 0;

			virtual bool isParent(const Type &target) const = 0;
		};
	}

	typedef Interfaces::Type IType;
}

#endif /* !STRUCTURED_SCRIPT_TYPE_INTERFACE_H */