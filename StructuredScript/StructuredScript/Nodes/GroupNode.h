#pragma once

#ifndef STRUCTURED_SCRIPT_GROUP_NODE_H
#define STRUCTURED_SCRIPT_GROUP_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

namespace StructuredScript{
	namespace Nodes{
		class GroupNode : public INode, public IGroupNode{
		public:
			explicit GroupNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual Ptr value() override;

		private:
			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_GROUP_NODE_H */