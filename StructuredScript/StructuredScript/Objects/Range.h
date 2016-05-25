#pragma once

#ifndef STRUCTURED_SCRIPT_RANGE_OBJECT_H
#define STRUCTURED_SCRIPT_RANGE_OBJECT_H

#include "Primitive.h"
#include "PrimitiveObject.h"

namespace StructuredScript{
	namespace Objects{
		class RangeBase : public Primitive, public PrimitiveObject{
		public:
			RangeBase();

			virtual Ptr ptr() override;

			static void init();

		protected:
			virtual void first_(Ptr value) = 0;

			virtual Ptr first_() = 0;

			virtual void second_(Ptr value) = 0;

			virtual Ptr second_() = 0;

			virtual bool ascending_() = 0;

			virtual bool descending_() = 0;

			static IType::Ptr class_;
			static INode::Ptr firstNode_;
			static INode::Ptr secondNode_;
		};

		template <class ObjectType, class ValueType>
		class Range : public RangeBase, public IRange{
		public:
			typedef std::pair<ValueType, ValueType> ValuePairType;

			Range(ValueType first, ValueType second)
				: value_(std::make_pair(first, second)){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void extend(IArrayObject &object, unsigned int index, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

		protected:
			virtual void first_(Ptr value) override;

			virtual Ptr first_() override;

			virtual void second_(Ptr value) override;

			virtual Ptr second_() override;

			virtual bool ascending_() override;

			virtual bool descending_() override;

			ValuePairType value_;
		};

		template <class ObjectType, class ValueType>
		void StructuredScript::Objects::Range<ObjectType, ValueType>::extend(IArrayObject &object, unsigned int index, IStorage *storage, IExceptionManager *exception, INode *expr){
			if (value_.first < value_.second){//Ascending
				if (index < object.size()){//Insert -- reversed
					for (auto value = value_.second; value >= value_.first; --value){
						object.insert(index, std::make_shared<ObjectType>(value), storage, exception, expr);
						if (Query::ExceptionManager::has(exception))
							return;

						if (value == static_cast<ValueType>(0))
							break;
					}
				}
				else{//Append
					for (auto value = value_.first; value <= value_.second; ++value){
						object.append(std::make_shared<ObjectType>(value), storage, exception, expr);
						if (Query::ExceptionManager::has(exception))
							return;
					}
				}
			}
			else{//Descending | Equal
				if (index < object.size()){//Insert -- reversed
					for (auto value = value_.second; value <= value_.first; ++value){
						object.insert(index, std::make_shared<ObjectType>(value), storage, exception, expr);
						if (Query::ExceptionManager::has(exception))
							return;
					}
				}
				else{//Append
					for (auto value = value_.first; value >= value_.second; --value){
						object.append(std::make_shared<ObjectType>(value), storage, exception, expr);
						if (Query::ExceptionManager::has(exception))
							return;

						if (value == static_cast<ValueType>(0))
							break;
					}
				}
			}
		}

		template <class ObjectType, class ValueType>
		bool StructuredScript::Objects::Range<ObjectType, ValueType>::descending_(){
			return (value_.second < value_.first);
		}

		template <class ObjectType, class ValueType>
		bool StructuredScript::Objects::Range<ObjectType, ValueType>::ascending_(){
			return (value_.first < value_.second);
		}

		template <class ObjectType, class ValueType>
		IAny::Ptr StructuredScript::Objects::Range<ObjectType, ValueType>::second_(){
			return std::make_shared<ObjectType>(value_.second);
		}

		template <class ObjectType, class ValueType>
		void StructuredScript::Objects::Range<ObjectType, ValueType>::second_(Ptr value){
			value_.second = static_cast<ValueType>(Query::Object::getIndexValue<long long>(value));
		}

		template <class ObjectType, class ValueType>
		IAny::Ptr StructuredScript::Objects::Range<ObjectType, ValueType>::first_(){
			return std::make_shared<ObjectType>(value_.first);
		}

		template <class ObjectType, class ValueType>
		void StructuredScript::Objects::Range<ObjectType, ValueType>::first_(Ptr value){
			value_.first = static_cast<ValueType>(Query::Object::getIndexValue<long long>(value));
		}

		template <class ObjectType, class ValueType>
		IAny::Ptr StructuredScript::Objects::Range<ObjectType, ValueType>::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
			return std::make_shared<Range>(value_.first, value_.second);
		}

		template <class ObjectType, class ValueType>
		std::string StructuredScript::Objects::Range<ObjectType, ValueType>::str(){
			return (std::to_string(value_.first) + "..." + std::to_string(value_.second));
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_RANGE_OBJECT_H */