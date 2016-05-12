#pragma once

#ifndef STRUCTURED_SCRIPT_IDENTIFIER_NODE_H
#define STRUCTURED_SCRIPT_IDENTIFIER_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"
#include "../Common/CompositeType.h"

namespace StructuredScript{
	namespace Nodes{
		class IdentifierNode : public INode, public IIdentifierNode, public IIdentifierExpressionNode{
		public:
			explicit IdentifierNode(const std::string &value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual std::string value() const override;

		private:
			std::string value_;
		};

		class OperatorIdentifierNode : public INode, public IIdentifierNode, public IOperatorIdentifierNode, public IIdentifierExpressionNode{
		public:
			explicit OperatorIdentifierNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual std::string value() const override;

			virtual INode::Ptr nodeValue() override;

		private:
			Ptr value_;
		};

		class PrimitiveTypeIdentifierNode : public IdentifierNode, public ITypeIdentifierNode{
		public:
			PrimitiveTypeIdentifierNode(const std::string &name, const std::string &value)
				: IdentifierNode(value), name_(name){}

			virtual Ptr clone() override;

			virtual std::string str() override;

		private:
			std::string name_;
		};

		class TypenameIdentifierNode : public INode, public IIdentifierNode, public ITypeIdentifierNode, public IIdentifierExpressionNode{
		public:
			explicit TypenameIdentifierNode(Ptr value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual std::string value() const override;

		protected:
			Ptr value_;
		};

		class TemplatedTypenameIdentifierNode : public TypenameIdentifierNode, public ITypeResolver{
		public:
			TemplatedTypenameIdentifierNode(Ptr type, Ptr value)
				: TypenameIdentifierNode(type), value_(value){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual IType::Ptr resolve(IStorage *storage) override;

		private:
			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_IDENTIFIER_NODE_H */