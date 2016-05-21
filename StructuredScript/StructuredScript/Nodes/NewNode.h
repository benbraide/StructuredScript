#pragma once

#ifndef STRUCTURED_SCRIPT_NEW_NODE_H
#define STRUCTURED_SCRIPT_NEW_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/TypeQuery.h"
#include "../Common/Factory.h"

#include "../Storage/FunctionMemory.h"

namespace StructuredScript{
	namespace Nodes{
		class NewNode : public INode{
		public:
			explicit NewNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			Ptr value();

		private:
			IType::Ptr resolveType_(Ptr target, IStorage *storage, IExceptionManager *exception, INode *expr);

			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NEW_NODE_H */