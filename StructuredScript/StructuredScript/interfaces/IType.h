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

			virtual Ptr base() = 0;

			virtual Storage *storage() = 0;

			virtual bool isAny() = 0;

			virtual bool isEqual(Ptr target) = 0;

			virtual bool isParent(Ptr target) = 0;

			virtual bool isCompatibleWith(Ptr target, bool family = false) = 0;

			virtual Ptr getCompatibleType(Ptr target, bool family = false) = 0;

			virtual std::string name() const = 0;

			virtual unsigned short states() const = 0;
		};
	}

	typedef Interfaces::Type IType;
}

#endif /* !STRUCTURED_SCRIPT_TYPE_INTERFACE_H */