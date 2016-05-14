#pragma once

#ifndef STRUCTURED_SCRIPT_ATTRIBUTE_SPAWNER_H
#define STRUCTURED_SCRIPT_ATTRIBUTE_SPAWNER_H

#include "../../Common/NodeQuery.h"

namespace StructuredScript{
	namespace Storage{
		template <class AttributeType, int Args = -1>
		class AttributeSpawner : public IMemoryAttribute{
		public:
			virtual Ptr ptr() override;

			virtual bool appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr spawn(INode::Ptr args, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr find(const std::string &name, IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};

		template <class AttributeType, int Args /*= -1*/>
		typename AttributeSpawner<AttributeType, Args>::Ptr StructuredScript::Storage::AttributeSpawner<AttributeType, Args>::find(const std::string &name,
			IStorage *storage, IExceptionManager *exception, INode *expr){
			return nullptr;
		}

		template <class AttributeType, int Args /*= -1*/>
		typename AttributeSpawner<AttributeType, Args>::Ptr StructuredScript::Storage::AttributeSpawner<AttributeType, Args>::spawn(INode::Ptr args,
			IStorage *storage, IExceptionManager *exception, INode *expr){
			if (Args != -1){
				Query::Node::ListType list;
				Query::Node::split(",", args, list);

				if (static_cast<int>(list.size()) != Args)
					return nullptr;
			}

			return std::make_shared<AttributeType>(args);
		}

		template <class AttributeType, int Args /*= -1*/>
		void StructuredScript::Storage::AttributeSpawner<AttributeType, Args>::apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){}

		template <class AttributeType, int Args /*= -1*/>
		void StructuredScript::Storage::AttributeSpawner<AttributeType, Args>::apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){}

		template <class AttributeType, int Args /*= -1*/>
		bool StructuredScript::Storage::AttributeSpawner<AttributeType, Args>::appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr){
			return false;
		}

		template <class AttributeType, int Args /*= -1*/>
		bool StructuredScript::Storage::AttributeSpawner<AttributeType, Args>::appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr){
			return false;
		}

		template <class AttributeType, int Args /*= -1*/>
		typename AttributeSpawner<AttributeType, Args>::Ptr StructuredScript::Storage::AttributeSpawner<AttributeType, Args>::ptr(){
			return shared_from_this();
		}

	}
}

#endif /* !STRUCTURED_SCRIPT_ATTRIBUTE_SPAWNER_H */