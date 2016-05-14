#pragma once

#ifndef STRUCTURED_SCRIPT_CALL_ATTRIBUTE_H
#define STRUCTURED_SCRIPT_CALL_ATTRIBUTE_H

#include "../../Common/NodeQuery.h"

namespace StructuredScript{
	namespace Storage{
		class CallAttribute : public IMemoryAttribute, public IAttributeWithArgument{
		public:
			CallAttribute(INode::Ptr arg)
				: arg_(arg){}

			virtual Ptr ptr() override;

			virtual bool appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr spawn(INode::Ptr args, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr find(const std::string &name, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual INode::Ptr arg() override;

		private:
			INode::Ptr arg_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_CALL_ATTRIBUTE_H */