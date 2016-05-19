#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_NODE_H
#define STRUCTURED_SCRIPT_FUNCTION_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "../Storage/FunctionMemory.h"
#include "../Objects/Function.h"
#include "../Interfaces/Nodes/IMemoryAdder.h"

namespace StructuredScript{
	namespace Nodes{
		class CallableNode{
		public:
			explicit CallableNode(INode::Ptr parameters)
				: parameters_(parameters){}

			virtual std::string str() = 0;

		protected:
			IAny::Ptr evaluate_(INode::Ptr name, IType::Ptr type, INode::Ptr definition, IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual std::shared_ptr<Objects::Function> create_(IType::Ptr type, INode::Ptr definition) = 0;

			INode::Ptr parameters_;
			IMemoryAttributes::Ptr attributes_;
		};

		class FunctionNode : public INode, public IFunctionNode, public CallableNode{
		public:
			FunctionNode(Ptr declaration, Ptr parameters)
				: CallableNode(parameters), declaration_(declaration){}

			virtual Ptr ptr() override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual Node::Ptr type() override;

			virtual Node::Ptr name() override;

			virtual Node::Ptr parameters() override;

		protected:
			IAny::Ptr evaluate_(Ptr definition, IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual std::shared_ptr<Objects::Function> create_(IType::Ptr type, INode::Ptr definition) override;

			Ptr declaration_;
		};

		class FunctionDeclarationNode : public FunctionNode, public IFunctionDeclarationNode{
		public:
			FunctionDeclarationNode(Ptr declaration, Ptr parameters)
				: FunctionNode(declaration, parameters){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};

		class FunctionDefinitionNode : public FunctionNode, public IFunctionDefinitionNode, public IBlockNode{
		public:
			FunctionDefinitionNode(Ptr declaration, Ptr parameters, Ptr definition)
				: FunctionNode(declaration, parameters), definition_(definition){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual Node::Ptr definition() override;

		private:
			Ptr definition_;
		};

		class ConstructorNode : public FunctionNode{
		public:
			typedef Objects::Constructor::InitializerListType InitializerListType;

			ConstructorNode(Ptr declaration, Ptr parameters, const InitializerListType &initializers)
				: FunctionNode(declaration, parameters), initializers_(initializers){}

			virtual Node::Ptr type() override;

			virtual Node::Ptr name() override;

			static void parseInitializers(Ptr initializers, InitializerListType &list, IExceptionManager *exception, INode *expr);

		protected:
			IAny::Ptr evaluate_(Ptr definition, IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual std::shared_ptr<Objects::Function> create_(IType::Ptr type, INode::Ptr definition) override;

			InitializerListType initializers_;
		};

		class ConstructorDeclarationNode : public ConstructorNode, public IFunctionDeclarationNode{
		public:
			ConstructorDeclarationNode(Ptr declaration, Ptr parameters, const InitializerListType &initializers)
				: ConstructorNode(declaration, parameters, initializers){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};

		class ConstructorDefinitionNode : public ConstructorNode, public IFunctionDefinitionNode, public IBlockNode{
		public:
			ConstructorDefinitionNode(Ptr declaration, Ptr parameters, const InitializerListType &initializers, Ptr definition)
				: ConstructorNode(declaration, parameters, initializers), definition_(definition){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual Node::Ptr definition() override;

		private:
			Ptr definition_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_NODE_H */