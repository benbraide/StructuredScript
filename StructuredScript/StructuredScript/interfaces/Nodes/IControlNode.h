#pragma once

#ifndef STRUCTURED_SCRIPT_CONTROL_NODE_INTERFACE_H
#define STRUCTURED_SCRIPT_CONTROL_NODE_INTERFACE_H

#include "../INode.h"

namespace StructuredScript{
	namespace Interfaces{
		class ControlNode{
		public:
			virtual ~ControlNode(){}
		};

		class IfControlNode{
		public:
			virtual ~IfControlNode(){}
		};

		class UnlessControlNode{
		public:
			virtual ~UnlessControlNode(){}
		};

		class WhileControlNode{
		public:
			virtual ~WhileControlNode(){}
		};

		class DoWhileControlNode{
		public:
			virtual ~DoWhileControlNode(){}
		};

		class ForControlNode{
		public:
			virtual ~ForControlNode(){}
		};

		class ElseControlNode{
		public:
			virtual ~ElseControlNode(){}
		};

		class ConditionalControlNode{
		public:
			virtual ~ConditionalControlNode(){}
		};

		class TryControlNode{
		public:
			virtual ~TryControlNode(){}
		};

		class CatchControlNode{
		public:
			virtual ~CatchControlNode(){}
		};

		class FinallyControlNode{
		public:
			virtual ~FinallyControlNode(){}
		};
	}

	typedef Interfaces::ControlNode				IControlNode;
	typedef Interfaces::IfControlNode			IIfControlNode;
	typedef Interfaces::UnlessControlNode		IUnlessControlNode;
	typedef Interfaces::WhileControlNode		IWhileControlNode;
	typedef Interfaces::DoWhileControlNode		IDoWhileControlNode;
	typedef Interfaces::ForControlNode			IForControlNode;
	typedef Interfaces::ElseControlNode			IElseControlNode;
	typedef Interfaces::ConditionalControlNode	IConditionalControlNode;
	typedef Interfaces::TryControlNode			ITryControlNode;
	typedef Interfaces::CatchControlNode		ICatchControlNode;
	typedef Interfaces::FinallyControlNode		IFinallyControlNode;
}

#endif /* !STRUCTURED_SCRIPT_CONTROL_NODE_INTERFACE_H */