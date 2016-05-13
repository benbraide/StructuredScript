#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_H
#define STRUCTURED_SCRIPT_FUNCTION_H

#include "Primitive.h"
#include "../Common/NodeQuery.h"
#include "../Common/TypeQuery.h"

namespace StructuredScript{
	namespace Objects{
		class Function : public Primitive, public IFunction{
		public:
			typedef std::pair<int, int> LimitsType;

			Function(IType::Ptr type, INode::Ptr parameters, INode::Ptr definition)
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_FUNCTION)), type_(type), parameters_(parameters), definition_(definition){}

			virtual bool init(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool accepts(int count) override;

			virtual int score(const ArgListType &args) override;

			virtual int score(const TypeListType &args) override;

			virtual Ptr call(const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) override;

		protected:
			int score_(IType::Ptr type, unsigned int index);

			IType::Ptr type_;
			INode::Ptr parameters_;
			INode::Ptr definition_;

			Query::Node::ListType list_;
			TypeListType types_;
			LimitsType limits_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_H */