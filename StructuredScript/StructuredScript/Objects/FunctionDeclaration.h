#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_DECLARATION_H
#define STRUCTURED_SCRIPT_FUNCTION_DECLARATION_H

#include "../Common/NodeQuery.h"
#include "../Common/TypeQuery.h"

#include "../Storage/FunctionStorage.h"
#include "../Storage/SpecializedStorage.h"

#include "Primitive.h"

namespace StructuredScript{
	namespace Objects{
		class FunctionDeclaration : public Primitive, public IFunction{
		public:
			typedef std::pair<int, int> LimitsType;

			FunctionDeclaration(IType::Ptr type, INode::Ptr parameters)
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_FUNCTION)), type_(type), parameters_(parameters){}

			virtual bool init(bool isRightUnary, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool isDefined() const override;

			virtual bool isStatic() const override;

			virtual bool isMember() const override;

			virtual bool equals(Any::Ptr target) override;

			virtual bool accepts(int count) override;

			virtual int score(bool rightUnary, IAny::Ptr object, const ArgListType &args) override;

			virtual int score(bool rightUnary, IAny::Ptr object, const TypeListType &args) override;

			virtual IType::Ptr declaredType() override;

		protected:
			IMemory::Ptr prep_(const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr);

			int score_(IType::Ptr type, unsigned int index);

			IType::Ptr getObjectType_(IAny::Ptr object);

			IType::Ptr type_;
			IType::Ptr owner_;

			bool isStatic_;
			bool rightUnary_;

			INode::Ptr parameters_;

			Query::Node::ListType list_;
			TypeListType types_;
			LimitsType limits_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_DECLARATION_H */