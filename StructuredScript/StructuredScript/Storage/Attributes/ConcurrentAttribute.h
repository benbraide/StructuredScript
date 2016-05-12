#pragma once

#ifndef STRUCTURED_SCRIPT_CONCURRENT_ATTRIBUTE_H
#define STRUCTURED_SCRIPT_CONCURRENT_ATTRIBUTE_H

#include "../../Common/NodeQuery.h"

namespace StructuredScript{
	namespace Storage{
		class ConcurentAttribute : public IMemoryAttribute{
		public:
			virtual Ptr ptr() override;

			virtual bool appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_CONCURRENT_ATTRIBUTE_H */