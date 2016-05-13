#pragma once

#ifndef STRUCTURED_SCRIPT_IDENTIFIER_NODE_H
#define STRUCTURED_SCRIPT_IDENTIFIER_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"
#include "../Common/Types/CompositeType.h"
#include "../Common/Types/DeclaredType.h"
#include "../Common/Types/StackedType.h"

#include "../Storage/MemoryState.h"

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

		class ExpandedTypenameIdentifierNode : public TypenameIdentifierNode, public IExpandedTypenameIdentifierNode, public ITypeResolver{
		public:
			explicit ExpandedTypenameIdentifierNode(Ptr value)
				: TypenameIdentifierNode(value){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual IType::Ptr resolve(IStorage *storage) override;
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

		class ModifiedTypenameIdentifierNode : public TypenameIdentifierNode, public IModifiedTypeIdentifierNode, public ITypeResolver{
		public:
			ModifiedTypenameIdentifierNode(Ptr type, const Storage::MemoryState &value)
				: TypenameIdentifierNode(type), value_(value){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void states(unsigned short value) override;

			virtual unsigned short states() const override;

			virtual IType::Ptr resolve(IStorage *storage) override;

		private:
			Storage::MemoryState value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_IDENTIFIER_NODE_H */