#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_MEMORY_ATTRIBUTES_H
#define STRUCTURED_SCRIPT_STORAGE_MEMORY_ATTRIBUTES_H

#include <map>

#include "../Common/NodeQuery.h"

#include "../Interfaces/Storages/IMemoryAttributes.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Storage{
		class MemoryAttributes : public IMemoryAttributes{
		public:
			typedef std::map<std::string, IMemoryAttribute::Ptr> ListType;

			MemoryAttributes(const ListType &attributes)
				: attributes_(attributes){}

			virtual Ptr ptr() override;

			virtual IMemoryAttribute::Ptr getAttribute(const std::string &name) override;

			virtual bool hasAttribute(const std::string &name) const override;

			virtual std::string str() const override;

			static bool parse(INode::Ptr attributes, INode::Ptr target, ListType &parsed);

			static IMemoryAttribute::Ptr resolve(INode::Ptr target, std::string &name);

		private:
			ListType attributes_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_MEMORY_ATTRIBUTES_H */