#pragma once

#ifndef STRUCTURED_SCRIPT_STACKED_TYPE_INTERFACE_H
#define STRUCTURED_SCRIPT_STACKED_TYPE_INTERFACE_H

#include "../IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class StackedType{
		public:
			virtual ~StackedType(){}

			virtual Type::Ptr value() = 0;
		};

		class ExpandedType{
		public:
			virtual ~ExpandedType(){}
		};

		class ArrayType{
		public:
			virtual ~ArrayType(){}
		};
	}

	typedef Interfaces::StackedType		IStackedType;
	typedef Interfaces::ExpandedType	IExpandedType;
	typedef Interfaces::ArrayType		IArrayType;
}

#endif /* !STRUCTURED_SCRIPT_STACKED_TYPE_INTERFACE_H */