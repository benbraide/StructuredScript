#pragma once

#ifndef STRUCTURED_SCRIPT_IDENTIFIER_NODE_H
#define STRUCTURED_SCRIPT_IDENTIFIER_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/Factory.h"

namespace StructuredScript{
	namespace Nodes{
		class IdentifierNode : public INode, public IIdentifierNode{
		public:
			explicit IdentifierNode(const std::string &value)
				: value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

		private:
			std::string value_;
		};

		class PrimitiveTypeIdentifierNode : public IdentifierNode{
		public:
			PrimitiveTypeIdentifierNode(const std::string &name, const std::string &value)
				: IdentifierNode(value), name_(name){}

			virtual Ptr clone() override;

			virtual std::string str() override;

		private:
			std::string name_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_IDENTIFIER_NODE_H */