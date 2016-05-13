#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARED_TYPE_INTERFACE_H
#define STRUCTURED_SCRIPT_DECLARED_TYPE_INTERFACE_H

#include "../IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class DeclaredType{
		public:
			virtual ~DeclaredType(){}

			virtual Type::Ptr value() = 0;

			virtual unsigned short states() const = 0;
		};
	}

	typedef Interfaces::DeclaredType IDeclaredType;
}

#endif /* !STRUCTURED_SCRIPT_DECLARED_TYPE_INTERFACE_H */