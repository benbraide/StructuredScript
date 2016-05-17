#pragma once

#include "SelectionNode.h"
#include "../Common/ExceptionManager.h"

namespace StructuredScript{
	namespace Nodes{
		class TryNode : public INode{
		public:
			TryNode(Ptr handler, Ptr value)
				: handler_(handler), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		private:
			Ptr handler_;
			Ptr value_;
		};

		class CatchNode : public NonIteratorNode<false>, public IExceptionHandler{
		public:
			CatchNode(Ptr predicate, Ptr value, Ptr next)
				: NonIteratorNode(predicate, value), next_(next){}

			virtual Ptr clone() override;

			virtual std::string str() override;

			virtual void finally(IStorage *storage, IExceptionManager *exception, INode *expr) override;

		protected:
			virtual IAny::Ptr evaluate_(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr else_(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth_(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			Ptr next_;
		};

		class FinallyNode : public INode, public IExceptionHandler{
		public:
			explicit FinallyNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual void finally(IStorage *storage, IExceptionManager *exception, INode *expr) override;

		private:
			Ptr value_;
		};
	}
}