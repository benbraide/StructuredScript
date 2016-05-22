#pragma once

#ifndef STRUCTURED_SCRIPT_ECHO_NODE_H
#define STRUCTURED_SCRIPT_ECHO_NODE_H

#include <iostream>

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Objects/Integer.h"
#include "../Objects/Real.h"

namespace StructuredScript{
	namespace Nodes{
		class EchoNode : public INode{
		public:
			explicit EchoNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			std::string str_(IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr);

			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ECHO_NODE_H */