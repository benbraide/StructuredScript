#pragma once

#ifndef STRUCTURED_SCRIPT_PROPERTY_NODE_H
#define STRUCTURED_SCRIPT_PROPERTY_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"
#include "../Common/Types/Type.h"

#include "../Storage/MemoryState.h"
#include "../Objects/Property.h"

namespace StructuredScript{
	namespace Nodes{
		class PropertyNode : public INode, public IPropertyNode{
		public:
			PropertyNode(Ptr declaration, Ptr value)
				: declaration_(declaration), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			Ptr declaration_;
			Ptr value_;
			IMemoryAttributes::Ptr attributes_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PROPERTY_NODE_H */