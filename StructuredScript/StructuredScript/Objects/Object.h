#pragma once

#ifndef STRUCTURED_SCRIPT_OBJECT_H
#define STRUCTURED_SCRIPT_OBJECT_H

#include <list>
#include <map>

#include "Any.h"
#include "../Storage/FunctionMemory.h"

namespace StructuredScript{
	namespace Objects{
		class Object : public Any, public IObject{
		public:
			typedef std::map<std::string, IMemory::Ptr>	ParentListType;
			typedef std::map<std::string, IMemory::Ptr>	MemoryListType;

			typedef StructuredScript::Storage::FunctionMemory::ListType ListType;

			explicit Object(IType::Ptr type)
				: Any(type){}

			virtual ~Object();

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IStorage *findStorage(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addMemory(const std::string &name) override;

			virtual IMemory::Ptr findMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr findFunctionMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr findOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

			virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual bool remove(IMemory::Ptr target) override;

			virtual void construct(const IFunction::ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IObject *findDirectParent(const std::string &name) override;

			void self(Any *self);

			bool addParent(const std::string &name, IMemory::Ptr parent);

		protected:
			void extendList_(ListType &list, const std::string &name, unsigned short searchScope);

			void extendOperatorList_(ListType &list, const std::string &name, unsigned short searchScope);

			void extendTypeOperatorList_(ListType &list, IType::Ptr name, unsigned short searchScope);

			Ptr callFunction_(IMemory::Ptr function, Ptr right, bool isRight, const std::string &value, bool silent, IExceptionManager *exception, INode *expr);

			void constructParents_(IStorage *storage, IExceptionManager *exception, INode *expr);

			Any *self_ = nullptr;
			MemoryListType objects_;
			ParentListType parents_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_OBJECT_H */