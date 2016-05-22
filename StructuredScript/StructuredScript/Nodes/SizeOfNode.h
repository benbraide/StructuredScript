#pragma once

#ifndef STRUCTURED_SCRIPT_SIZE_OF_NODE_H
#define STRUCTURED_SCRIPT_SIZE_OF_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/Objects/IPrimitiveObject.h"

namespace StructuredScript{
	namespace Nodes{
		class SizeOfNode : public INode{
		public:
			explicit SizeOfNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_SIZE_OF_NODE_H */