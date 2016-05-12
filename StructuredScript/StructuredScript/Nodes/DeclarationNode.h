#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARATION_NODE_H
#define STRUCTURED_SCRIPT_DECLARATION_NODE_H

#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"

#include "../Storage/MemoryState.h"
#include "../Storage/MemoryAttributes.h"
#include "../Storage/Memory.h"
#include "../Storage/FunctionMemory.h"

namespace StructuredScript{
	namespace Nodes{
		class SharedDeclaration{
		public:
			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual std::string str() = 0;

			virtual IMemory::Ptr allocate(IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual INode::Ptr type() = 0;

			virtual INode::Ptr value() = 0;

			virtual unsigned short states() = 0;

			virtual IMemoryAttributes *attributes() = 0;
		};

		class DeclarationNode : public SharedDeclaration, public INode, public IDeclarationNode{
		public:
			DeclarationNode(Ptr type, Ptr value)
				: type_(type), value_(value), state_(Storage::MemoryState::STATE_NONE), attributes_({}){}

			DeclarationNode(Ptr type, Ptr value, const Storage::MemoryState &state, const Storage::MemoryAttributes &attributes)
				: type_(type), value_(value), state_(state), attributes_(attributes){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual IMemory::Ptr allocate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr type() override;

			virtual Ptr value() override;

			virtual void states(unsigned short value) override;

			virtual unsigned short states() override;

			virtual void attributes(const Storage::MemoryAttributes &value) override;

			virtual IMemoryAttributes *attributes() override;

		private:
			Ptr type_;
			Ptr value_;
			Storage::MemoryState state_;
			Storage::MemoryAttributes attributes_;
		};

		class CommonDeclaration : public INode, public IDeclarationNode{
		public:
			CommonDeclaration(Ptr declaration, Ptr value);

			virtual Ptr ptr() override;

			virtual Ptr type() override;

			virtual Ptr value() override;

			virtual void states(unsigned short value) override;

			virtual unsigned short states() override;

			virtual void attributes(const Storage::MemoryAttributes &value) override;

			virtual IMemoryAttributes *attributes() override;

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

			virtual unsigned short states() override;

			virtual IMemoryAttributes *attributes() override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_DECLARATION_NODE_H */