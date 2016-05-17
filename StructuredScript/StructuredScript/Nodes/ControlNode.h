#pragma once

#ifndef STRUCTURED_SCRIPT_CONTROL_NODE_H
#define STRUCTURED_SCRIPT_CONTROL_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "../Storage/SpecializedStorage.h"

namespace StructuredScript{
	namespace Nodes{
		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		class ControlNode : public INode, public IControlNode{
		public:
			ControlNode(Ptr value, Ptr predicate = nullptr)
				: value_(value), predicate_(predicate){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

		protected:
			virtual IAny::Ptr evaluate_(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual IAny::Ptr else_(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual void before_(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual bool truth_(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual void after_(IStorage *storage, IExceptionManager *exception, INode *expr);

			Ptr value_;
			Ptr predicate_;
			IMemoryAttributes::Ptr attributes_;
		};

		template <class ControlType>
		class ControlExtension : public ControlType{
		public:
			template <typename ...Ty>
			explicit ControlExtension(INode::Ptr elseNode, Ty... args)
				: ControlType(args...), elseNode_(elseNode){}

			virtual ~ControlExtension(){}

			virtual INode::Ptr clone();

			virtual std::string str();

		protected:
			virtual IAny::Ptr else_(IStorage *storage, IExceptionManager *exception, INode *expr);

			INode::Ptr elseNode_;
		};

		template <class ControlType>
		IAny::Ptr StructuredScript::Nodes::ControlExtension<ControlType>::else_(IStorage *storage, IExceptionManager *exception, INode *expr){
			return elseNode_->evaluate(storage, exception, expr);
		}

		template <class ControlType>
		std::string StructuredScript::Nodes::ControlExtension<ControlType>::str(){
			return ("else " + ControlType::str());
		}

		template <class ControlType>
		INode::Ptr StructuredScript::Nodes::ControlExtension<ControlType>::clone(){
			return ControlType::clone_<ControlExtension>(elseNode_);
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		IAny::Ptr StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::else_(IStorage *storage, IExceptionManager *exception, INode *expr){
			return nullptr;
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		void StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::after_(IStorage *storage, IExceptionManager *exception, INode *expr){}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		bool StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::truth_(IStorage *storage, IExceptionManager *exception, INode *expr){
			if (predicate_ == nullptr || Query::Node::isEmpty(predicate_))
				return false;

			auto value = predicate_->evaluate(storage, exception, expr);
			return Query::ExceptionManager::has(exception) ? false : value->truth(storage, exception, expr);
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		void StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::before_(IStorage *storage, IExceptionManager *exception, INode *expr){}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		IAny::Ptr StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::evaluate_(IStorage *storage, IExceptionManager *exception, INode *expr){
			Storage::Storage localStorage(nullptr);
			Storage::SharedStorage sharedStorage(localStorage, *storage);

			return (value_ == nullptr || Query::Node::isEmpty(value_)) ? nullptr : value_->evaluate(&sharedStorage, exception, expr);
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		IMemoryAttributes::Ptr StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::attributes(){
			return attributes_;
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		void StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::attributes(IMemoryAttributes::Ptr attributes){
			attributes_ = attributes;
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		std::string StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::str(){
			return "";
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		IAny::Ptr StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
			Storage::Storage localStorage(storage);

			before_(&localStorage, exception, expr);
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			IAny::Ptr value;
			if (SkipFirstCheck || truth_(&localStorage, exception, expr)){
				do{
					value = evaluate_(&localStorage, exception, expr);
					if (Query::ExceptionManager::has(exception)){
						if (Query::ExceptionManager::hasBreak(exception)){
							if (!Iterate){// 'break' requires loop
								return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
									Query::ExceptionManager::combine("'break' found outside loop!", expr)));
							}

							break;
						}
						else if (Query::ExceptionManager::hasContinue(exception)){
							if (!Iterate){// 'continue' requires loop
								return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
									Query::ExceptionManager::combine("'continue' found outside loop!", expr)));
							}

							continue;
						}
						else//Other
							return nullptr;
					}

					after_(&localStorage, exception, expr);
					if (Query::ExceptionManager::has(exception))
						return nullptr;

				} while (Iterate && truth_(&localStorage, exception, expr));
			}
			else
				value = else_(storage, exception, expr);

			if (Query::ExceptionManager::has(exception))
				return nullptr;

			return (ReturnValue && value != nullptr) ? value : PrimitiveFactory::createUndefined();
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		INode::Ptr StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::clone(){
			return nullptr;
		}

		template <bool Iterate, bool SkipFirstCheck, bool ReturnValue>
		INode::Ptr StructuredScript::Nodes::ControlNode<Iterate, SkipFirstCheck, ReturnValue>::ptr(){
			return shared_from_this();
		}

		typedef ControlNode<true, false, false>		IteratorNode;
		typedef ControlNode<true, true, false>		SkippingIteratorNode;
	}
}

#endif /* !STRUCTURED_SCRIPT_CONTROL_NODE_H */