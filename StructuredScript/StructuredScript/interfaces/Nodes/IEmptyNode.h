#pragma once

#ifndef STRUCTURED_SCRIPT_EMPTY_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_EMPTY_NODE_INTERFACE_H

namespace StructuredScript{
	namespace Interfaces{
		class EmptyNode{
		public:
			virtual ~EmptyNode(){}
		};
	}

	typedef Interfaces::EmptyNode IEmptyNode;
}

#endif /* !STRUCTURED_SCRIPT_EMPTY_NODE_INTERFACE_H */