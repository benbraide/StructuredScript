#pragma once

#ifndef STRUCTURED_SCRIPT_NAMESPACE_NODE_H
#define STRUCTURED_SCRIPT_NAMESPACE_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Storage/Namespace.h"

namespace StructuredScript{
	namespace Nodes{
		class NamespaceNode : public INode, public IBlockNode{
		public:
			NamespaceNode(Ptr name, Ptr value)
				: name_(name), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			Ptr name_;
			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NAMESPACE_NODE_H */