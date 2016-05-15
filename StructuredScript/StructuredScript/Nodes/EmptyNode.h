#pragma once

#ifndef STRUCTURED_SCRIPT_EMPTY_NODE_H
#define STRUCTURED_SCRIPT_EMPTY_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

namespace StructuredScript{
	namespace Nodes{
		class EmptyNode : public INode, public IEmptyNode{
		public:
			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_EMPTY_NODE_H */