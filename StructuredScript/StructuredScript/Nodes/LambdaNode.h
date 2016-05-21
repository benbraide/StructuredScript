#pragma once

#ifndef STRUCTURED_SCRIPT_LAMBDA_NODE_H
#define STRUCTURED_SCRIPT_LAMBDA_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "../Storage/MemoryAttributes.h"

#include "EmptyNode.h"
#include "FunctionNode.h"
#include "BlockPairNode.h"
#include "NewNode.h"

namespace StructuredScript{
	namespace Nodes{
		class LambdaNode : public INode{
		public:
			LambdaNode(Ptr captures, Ptr parameters, Ptr type, Ptr value)
				: captures_(captures), parameters_(parameters), type_(type), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			bool parseCapture_(const std::string &prefix, Ptr capture, std::string &parameters, std::string &initializers, std::string &fields,
				std::string &values, IExceptionManager *exception, INode *expr);

			void append_(const std::string &prefix, const std::string &captureStr, std::string &parameters, std::string &initializers,
				std::string &fields, std::string &values);

			Ptr captures_;
			Ptr parameters_;
			Ptr type_;
			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_LAMBDA_NODE_H */