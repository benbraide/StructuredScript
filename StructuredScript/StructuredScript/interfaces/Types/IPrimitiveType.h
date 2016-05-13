#pragma once

#ifndef STRUCTURED_SCRIPT_PRIMITIVE_TYPE_INTERFACE_H
#define STRUCTURED_SCRIPT_PRIMITIVE_TYPE_INTERFACE_H

#include "../../Common/Typename.h"

namespace StructuredScript{
	namespace Interfaces{
		class PrimitiveType{
		public:
			virtual ~PrimitiveType(){}

			virtual Typename value() const = 0;
		};

		class AnyType{
		public:
			virtual ~AnyType(){}
		};

		class CompositePrimitiveType{
		public:
			virtual ~CompositePrimitiveType(){}
		};
	}

	typedef Interfaces::PrimitiveType			IPrimitiveType;
	typedef Interfaces::AnyType					IAnyType;
	typedef Interfaces::CompositePrimitiveType	ICompositePrimitiveType;
}

#endif /* !STRUCTURED_SCRIPT_PRIMITIVE_TYPE_INTERFACE_H */