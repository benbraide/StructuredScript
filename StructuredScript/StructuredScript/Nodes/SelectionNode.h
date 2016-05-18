#pragma once

#ifndef STRUCTURED_SCRIPT_SELECTION_NODE_H
#define STRUCTURED_SCRIPT_SELECTION_NODE_H

#include "ControlNode.h"

namespace StructuredScript{
	namespace Nodes{
		template <bool ReturnValue>
		class NonIteratorNode : public ControlNode<false, false, ReturnValue>{
		public:
			typedef ControlNode<false, false, ReturnValue> BaseType;

			NonIteratorNode(Ptr predicate, Ptr value)
				: BaseType(value, predicate){}

		protected:
			template <typename ExtensionType>
			Ptr clone_(Ptr elseNode){
				return nullptr;
			}
		};

		class IfNode : public NonIteratorNode<false>, public IBlockNode{
		public:
			IfNode(Ptr predicate, Ptr value)
				: NonIteratorNode(predicate, value){}

			virtual Ptr clone() override;

			virtual std::string str() override;

		protected:
			template <typename ExtensionType>
			Ptr clone_(Ptr elseNode);
		};

		template <typename ExtensionType>
		INode::Ptr StructuredScript::Nodes::IfNode::clone_(Ptr elseNode){
			return std::make_shared<ExtensionType>(elseNode->clone(), predicate_->clone(), value_->clone());
		}

		class UnlessNode : public NonIteratorNode<false>, public IBlockNode{
		public:
			UnlessNode(Ptr predicate, Ptr value)
				: NonIteratorNode(predicate, value){}

			virtual Ptr clone() override;

			virtual std::string str() override;

		protected:
			virtual bool truth_(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			template <typename ExtensionType>
			Ptr clone_(Ptr elseNode);
		};

		template <typename ExtensionType>
		INode::Ptr StructuredScript::Nodes::UnlessNode::clone_(Ptr elseNode){
			return std::make_shared<ExtensionType>(elseNode->clone(), predicate_->clone(), value_->clone());
		}

		class ElseNode : public NonIteratorNode<false>, public IBlockNode{
		public:
			ElseNode(Ptr value)
				: NonIteratorNode(nullptr, value){}

			virtual Ptr clone() override;

			virtual std::string str() override;

		protected:
			virtual bool truth_(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};

		class ConditionalNode : public ControlExtension< NonIteratorNode<true> >{
		public:
			ConditionalNode(Ptr predicate, Ptr left, Ptr right)
				: ControlExtension(right, predicate, left){}

			virtual Ptr clone() override;

			virtual std::string str() override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_SELECTION_NODE_H */