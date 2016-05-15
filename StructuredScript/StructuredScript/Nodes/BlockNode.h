#pragma once

#ifndef STRUCTURED_SCRIPT_BLOCK_NODE_H
#define STRUCTURED_SCRIPT_BLOCK_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

namespace StructuredScript{
	namespace Nodes{
		class BlockNode : public INode, public IBlockNode{
		public:
			explicit BlockNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual Ptr value() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			Ptr value_;
			IMemoryAttributes::Ptr attributes_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_BLOCK_NODE_H */