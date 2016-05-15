#pragma once

#ifndef STRUCTURED_SCRIPT_INTERRUPT_NODE_H
#define STRUCTURED_SCRIPT_INTERRUPT_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

namespace StructuredScript{
	namespace Nodes{
		class ReturnNode : public INode{
		public:
			explicit ReturnNode(Ptr value)
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

		class InterruptCommon : public INode{
		public:
			virtual Ptr ptr() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;
		};

		class BreakNode : public InterruptCommon{
		public:
			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;
		};

		class ContinueNode : public InterruptCommon{
		public:
			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_INTERRUPT_NODE_H */