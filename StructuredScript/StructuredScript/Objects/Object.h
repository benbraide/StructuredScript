#pragma once

#ifndef STRUCTURED_SCRIPT_OBJECT_H
#define STRUCTURED_SCRIPT_OBJECT_H

#include <list>
#include <map>

#include "Any.h"

namespace StructuredScript{
	namespace Objects{
		class Object : public Any{
		public:
			typedef std::list<Any *>					ParentListType;
			typedef std::map<std::string, IMemory::Ptr>	MemoryListType;

			explicit Object(IType::Ptr type)
				: Any(type), self_(this){}

			virtual ~Object(){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

			virtual IStorage *findStorage(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IType::Ptr *addType(const std::string &name) override;

			virtual IType::Ptr findType(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addMemory(const std::string &name) override;

			virtual IMemory::Ptr findMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addTypenameOperatorMemory(IType::Ptr name) override;

			virtual IMemory::Ptr findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

			virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual bool remove(IMemory::Ptr target) override;

			void self(Any *self);

		protected:
			Any *self_;
			MemoryListType objects_;
			ParentListType parents_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_OBJECT_H */