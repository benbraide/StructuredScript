#pragma once

#ifndef STRUCTURED_SCRIPT_CLASS_NODE_H
#define STRUCTURED_SCRIPT_CLASS_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Common/Types/Class.h"

namespace StructuredScript{
	namespace Nodes{
		class ClassNode : public INode, public IClassNode{
		public:
			ClassNode(Ptr name, Ptr value)
				: name_(name), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual IType::Ptr create(IStorage *storage, IExceptionManager *exception, INode *expr) override;

		protected:
			virtual void getParents_(Class::ParentListType &parents, IStorage *storage, IExceptionManager *exception, INode *expr);

			bool isStatic_(IDeclarationNode *declaration);

			Ptr name_;
			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_CLASS_NODE_H */