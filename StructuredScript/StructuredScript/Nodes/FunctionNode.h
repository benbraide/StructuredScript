#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_NODE_H
#define STRUCTURED_SCRIPT_FUNCTION_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "../Storage/FunctionMemory.h"
#include "../Objects/Function.h"

namespace StructuredScript{
	namespace Nodes{
		class FunctionNode : public INode, public IFunctionNode{
		public:
			FunctionNode(Ptr declaration, Ptr parameters)
				: declaration_(declaration), parameters_(parameters){}

			virtual Ptr ptr() override;

			virtual std::string str() override;

			virtual Node::Ptr type() override;

			virtual Node::Ptr name() override;

			virtual Node::Ptr parameters() override;

		protected:
			IAny::Ptr evaluate_(Ptr definition, IStorage *storage, IExceptionManager *exception, INode *expr);

			Ptr declaration_;
			Ptr parameters_;
		};

		class FunctionDeclarationNode : public FunctionNode, public IFunctionDeclarationNode{
		public:
			FunctionDeclarationNode(Ptr declaration, Ptr parameters)
				: FunctionNode(declaration, parameters){}

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};

		class FunctionDefinitionNode : public FunctionNode, public IFunctionDefinitionNode{
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
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_NODE_H */