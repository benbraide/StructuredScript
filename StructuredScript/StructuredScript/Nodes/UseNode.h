#pragma once

#ifndef STRUCTURED_SCRIPT_USE_NODE_H
#define STRUCTURED_SCRIPT_USE_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

namespace StructuredScript{
	namespace Nodes{
		class UseNode : public INode{
		public:
			UseNode(Ptr value, bool storage)
				: value_(value), storage_(storage){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			Ptr value_;
			bool storage_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_USE_NODE_H */