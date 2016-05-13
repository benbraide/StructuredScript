#pragma once

#ifndef STRUCTURED_SCRIPT_COMPOSITE_TYPE_INTERFACE_H
#define STRUCTURED_SCRIPT_COMPOSITE_TYPE_INTERFACE_H

#include "../IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class CompositeType{
		public:
			virtual ~CompositeType(){}

			virtual bool isReversedEqual(Type::Ptr target) = 0;

			virtual bool isReversedParent(Type::Ptr target) = 0;

			virtual bool isReversedCompatibleWith(Type::Ptr target, bool family = false) = 0;

			virtual Type::Ptr getReversedCompatibleType(Type::Ptr target, bool family = false) = 0;
		};
	}

	typedef Interfaces::CompositeType ICompositeType;
}

#endif /* !STRUCTURED_SCRIPT_COMPOSITE_TYPE_INTERFACE_H */