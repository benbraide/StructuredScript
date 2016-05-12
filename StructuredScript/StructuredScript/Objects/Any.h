#pragma once

#ifndef STRUCTURED_SCRIPT_ANY_OBJECT_H
#define STRUCTURED_SCRIPT_ANY_OBJECT_H

#include <list>
#include <map>

#include "../Common/ExceptionManagerQuery.h"

namespace StructuredScript{
	namespace Objects{
		class Any : public IAny, public IStorage{
		public:
			typedef std::list<Any *>					ParentListType;
			typedef std::map<std::string, IMemory::Ptr>	MemoryListType;

			explicit Any(IType::Ptr type)
				: type_(type), self_(this){}

			virtual ~Any(){}

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny *base() override;

			virtual IType::Ptr type() override;

			virtual void setMemory(IMemory *memory) override;

			virtual IMemory *memory() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

			virtual IStorage *findStorage(const std::string &name, bool localOnly) override;

			virtual IType::Ptr *addType(const std::string &name) override;

			virtual IType::Ptr findType(const std::string &name, bool localOnly) override;

			virtual IMemory::Ptr *addMemory(const std::string &name) override;

			virtual IMemory::Ptr findMemory(const std::string &name, bool localOnly) override;

			virtual IMemory::Ptr *addOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findOperatorMemory(const std::string &name, bool localOnly) override;

			virtual IMemory::Ptr *addTypenameOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findTypenameOperatorMemory(const std::string &name, bool localOnly) override;

			virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

			virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, bool localOnly) override;

			virtual bool remove(IMemory::Ptr target) override;

			void setSelf(Any *self){
				self_ = self;
			}

		protected:
			IType::Ptr type_;
			IMemory *memory_ = nullptr;

			Any *self_;

			MemoryListType objects_;
			ParentListType parents_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ANY_OBJECT_H */