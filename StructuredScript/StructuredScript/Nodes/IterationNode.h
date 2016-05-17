#pragma once

#ifndef STRUCTURED_SCRIPT_ITERATION_NODE_H
#define STRUCTURED_SCRIPT_ITERATION_NODE_H

#include "ControlNode.h"
#include "EmptyNode.h"

namespace StructuredScript{
	namespace Nodes{
		class WhileNode : public IteratorNode{
		public:
			WhileNode(Ptr predicate, Ptr value)
				: IteratorNode(value, predicate){}

			virtual Ptr clone() override;

			virtual std::string str() override;

		protected:
			template <typename ExtensionType>
			Ptr clone_(Ptr elseNode);
		};

		template <typename ExtensionType>
		INode::Ptr StructuredScript::Nodes::WhileNode::clone_(Ptr elseNode){
			return std::make_shared<ExtensionType>(elseNode->clone(), predicate_->clone(), value_->clone());
		}

		class DoWhileNode : public SkippingIteratorNode{
		public:
			DoWhileNode(Ptr predicate, Ptr value)
				: SkippingIteratorNode(value, predicate){}

			virtual Ptr clone() override;

			virtual std::string str() override;
		};

		class ForNode : public IteratorNode{
		public:
			ForNode(Ptr predicate, Ptr value);

			ForNode(Ptr init, Ptr predicate, Ptr update, Ptr value)
				: IteratorNode(value, predicate), init_(init), update_(update){}

			virtual Ptr clone() override;

			virtual std::string str() override;

		protected:
			virtual void before_(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void after_(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			template <typename ExtensionType>
			Ptr clone_(Ptr elseNode);

			Ptr init_;
			Ptr update_;
		};

		template <typename ExtensionType>
		INode::Ptr StructuredScript::Nodes::ForNode::clone_(Ptr elseNode){
			if (init_ == nullptr || update_ == nullptr)
				return std::make_shared<ExtensionType>(elseNode->clone(), nullptr, predicate_->clone(), nullptr, value_->clone());
			return std::make_shared<ExtensionType>(elseNode->clone(), init_->clone(), predicate_->clone(), update_->clone(), value_->clone());
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_ITERATION_NODE_H */