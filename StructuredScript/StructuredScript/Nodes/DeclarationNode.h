#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARATION_NODE_H
#define STRUCTURED_SCRIPT_DECLARATION_NODE_H

#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Types/DeclaredType.h"

#include "../Storage/MemoryState.h"
#include "../Storage/FunctionMemory.h"

#include "../Objects/Expansion.h"

namespace StructuredScript{
	namespace Nodes{
		class SharedDeclaration{
		public:
			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual std::string str() = 0;

			virtual IMemory::Ptr allocate(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual INode::Ptr type() = 0;

			virtual INode::Ptr value() = 0;

			virtual IMemoryAttributes::Ptr attributes() = 0;

		private:
			IType::Ptr resolveType_(IStorage *storage, IExceptionManager *exception, INode *expr);

			IMemory::Ptr createMemory_(IStorage::MemoryInfo *info, IStorage *storage, IType::Ptr type);
		};

		class DeclarationNode : public SharedDeclaration, public INode, public IDeclarationNode, public IClassEntry{
		public:
			DeclarationNode(Ptr type, Ptr value)
				: type_(type), value_(value), attributes_({}){}

			DeclarationNode(Ptr type, Ptr value, IMemoryAttributes::Ptr attributes)
				: type_(type), value_(value), attributes_(attributes){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual IMemory::Ptr allocate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr type() override;

			virtual Ptr value() override;

			virtual void attributes(IMemoryAttributes::Ptr value) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual std::string declName() override;

		private:
			Ptr type_;
			Ptr value_;
			IMemoryAttributes::Ptr attributes_;
		};

		class CommonDeclaration : public INode, public IDeclarationNode, public IClassEntry{
		public:
			CommonDeclaration(Ptr declaration, Ptr value);

			virtual Ptr ptr() override;

			virtual Ptr type() override;

			virtual Ptr value() override;

			virtual void attributes(IMemoryAttributes::Ptr value) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual std::string declName() override;

		protected:
			Ptr declaration_;
			Ptr value_;
		};

		class InitializationNode : public CommonDeclaration, public IInitializationNode{
		public:
			InitializationNode(Ptr declaration, Ptr value)
				: CommonDeclaration(declaration, value){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual IMemory::Ptr allocate(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};

		class DependentDeclarationNode : public CommonDeclaration, public SharedDeclaration{
		public:
			DependentDeclarationNode(Ptr declaration, Ptr value)
				: CommonDeclaration(declaration, value){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual IMemory::Ptr allocate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr type() override;

			virtual Ptr value() override;

			virtual IMemoryAttributes::Ptr attributes() override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_DECLARATION_NODE_H */