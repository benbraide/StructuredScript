#pragma once

#ifndef STRUCTURED_SCRIPT_USE_ADDER_INTERFACE_H
#define STRUCTURED_SCRIPT_USE_ADDER_INTERFACE_H

#include "../INode.h"
#include "../Storages/IPureStorage.h"

namespace StructuredScript{
	namespace Interfaces{
		class UseAdder{
		public:
			virtual ~UseAdder(){}

			virtual bool use(PureStorage *target, Storage *storage) = 0;
		};
	}

	typedef Interfaces::UseAdder IUseAdder;
}

#endif /* !STRUCTURED_SCRIPT_USE_ADDER_INTERFACE_H */