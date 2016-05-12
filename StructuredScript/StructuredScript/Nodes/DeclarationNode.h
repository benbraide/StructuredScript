#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARATION_NODE_H
#define STRUCTURED_SCRIPT_DECLARATION_NODE_H

#include "../Common/NodeQuery.h"

#include "../Storage/MemoryState.h"
#include "../Storage/MemoryAttributes.h"
#include "../Storage/Memory.h"
#include "../Storage/FunctionMemory.h"

namespace StructuredScript{
	namespace Nodes{
		class DeclarationNode : public INode, public IDeclarationNode{
		public:
			DeclarationNode(Ptr type, Ptr value, const Storage::MemoryState &state, const Storage::MemoryAttributes &attributes)
				: type_(type), value_(value), state_(state), attributes_(attributes){}

			virtual Ptr ptr() override;

			virtual Ptr clone() override;

			virtual IAny::Ptr evaluate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str() override;

			virtual IMemory::Ptr allocate(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr type() override;

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
	}
}

#endif /* !STRUCTURED_SCRIPT_DECLARATION_NODE_H */