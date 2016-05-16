#pragma once

#ifndef STRUCTURED_SCRIPT_OPERATOR_NODE_H
#define STRUCTURED_SCRIPT_OPERATOR_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/Objects/IPrimitiveObject.h"
#include "../Interfaces/Storages/IFunctionMemory.h"

namespace StructuredScript{
	namespace Nodes{
		class UnaryOperatorNode : public INode, public IUnaryOperatorNode, public IStorageResolver, public ITypeResolver, public IMemoryResolver{
		public:
			UnaryOperatorNode(bool left, const std::string &value, Ptr operand)
				: left_(left), value_(value), operand_(operand){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual std::string value() const override;

			virtual Ptr operand() override;

			virtual IStorage *resolveStorage(IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT) override;

			virtual IType::Ptr resolveType(IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT) override;

			virtual IMemory::Ptr resolveMemory(IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT) override;

		protected:
			bool left_;
			std::string value_;
			Ptr operand_;
		};

		class BinaryOperatorNode : public INode, public IBinaryOperatorNode, public IStorageResolver, public ITypeResolver, public IMemoryResolver{
		public:
			BinaryOperatorNode(const std::string &value, Ptr leftOperand, Ptr rightOperand)
				: value_(value), leftOperand_(leftOperand), rightOperand_(rightOperand){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual std::string value() const override;

			virtual Ptr leftOperand() override;

			virtual Ptr rightOperand() override;

			virtual IStorage *resolveStorage(IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT) override;

			virtual IType::Ptr resolveType(IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT) override;

			virtual IMemory::Ptr resolveMemory(IStorage *storage, unsigned short searchScope = IStorage::SEARCH_DEFAULT) override;

		protected:
			std::string value_;
			Ptr leftOperand_;
			Ptr rightOperand_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_OPERATOR_NODE_H */