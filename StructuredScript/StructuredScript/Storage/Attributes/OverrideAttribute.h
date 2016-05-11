#pragma once

#ifndef STRUCTURED_SCRIPT_OVERRIDE_ATTRIBUTE_H
#define STRUCTURED_SCRIPT_OVERRIDE_ATTRIBUTE_H

#include "../../Common/NodeQuery.h"

namespace StructuredScript{
	namespace Storage{
		class OverrideAttribute : public IMemoryAttribute{
		public:
			virtual Ptr ptr() override;

			virtual bool appliesTo(IMemory *memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool appliesTo(INode *node, IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_OVERRIDE_ATTRIBUTE_H */