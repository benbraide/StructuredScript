#pragma once

#ifndef STRUCTURED_SCRIPT_PROPERTY_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_PROPERTY_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class PropertyNode{
		public:
			virtual ~PropertyNode(){}

			virtual Node::Ptr declaration() = 0;
		};
	}

	typedef Interfaces::PropertyNode IPropertyNode;
}

#endif /* !STRUCTURED_SCRIPT_PROPERTY_NODE_INTERFACE_H */