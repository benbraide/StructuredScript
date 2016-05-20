#pragma once

#ifndef STRUCTURED_SCRIPT_ENUM_NODE_H
#define STRUCTURED_SCRIPT_ENUM_NODE_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/NodeQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Common/Types/Type.h"
#include "../Common/Types/DeclaredType.h"

namespace StructuredScript{
	namespace Nodes{
		class EnumNode : public INode, public IClassEntry, public IBlockNode{
		public:
			EnumNode(Ptr name, Ptr value)
				: name_(name), value_(value){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual void attributes(IMemoryAttributes::Ptr attributes) override;

			virtual IMemoryAttributes::Ptr attributes() override;

			virtual std::string declName() override;

		private:
			Ptr name_;
			Ptr value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ENUM_NODE_H */