#pragma once

#ifndef STRUCTURED_SCRIPT_TYPE_INTERFACE_H
#define STRUCTURED_SCRIPT_TYPE_INTERFACE_H

#include <memory>

#include "IStorage.h"

namespace StructuredScript{
	namespace Interfaces{
		class Type : protected std::enable_shared_from_this<Type>{
		public:
			typedef std::shared_ptr<Type> Ptr;

			virtual ~Type(){}

			virtual Ptr ptr() = 0;

			virtual Storage *storage() = 0;

			virtual bool isEqual(const Type &target) const = 0;

			virtual bool isParent(const Type &target) const = 0;

			virtual bool isCompatibleWith(const Type &target) const = 0;

			virtual Ptr getCompatibleType(const Type &target) = 0;

			virtual std::string name() const = 0;
		};
	}

	typedef Interfaces::Type IType;
}

#endif /* !STRUCTURED_SCRIPT_TYPE_INTERFACE_H */