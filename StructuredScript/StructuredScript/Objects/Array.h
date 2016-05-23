#pragma once

#ifndef STRUCTURED_SCRIPT_ARRAY_OBJECT_H
#define STRUCTURED_SCRIPT_ARRAY_OBJECT_H

#include <vector>

#include "Primitive.h"
#include "PrimitiveObject.h"

#include "../Common/ExceptionManager.h"

namespace StructuredScript{
	namespace Objects{
		class ArrayObject : public Primitive, public PrimitiveObject, public IArrayObject{
		public:
			typedef IArrayObject::MemoryListType MemoryListType;

			explicit ArrayObject();

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr at(unsigned int index) override;

			virtual void append(IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void insert(unsigned int index, IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void insert(MemoryListType::iterator index, IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void erase(unsigned int index) override;

			virtual void erase(MemoryListType::iterator index) override;

			virtual void clear() override;

			virtual bool empty() override;

			virtual void size(unsigned int value, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual unsigned int size() override;

			virtual const MemoryListType &list() const override;

			static void init();

		protected:
			IMemory::Ptr add_(MemoryListType::iterator where, IType::Ptr type);

			void grow_(IStorage *storage, IExceptionManager *exception, INode *expr);

			MemoryListType entries_;

			static IType::Ptr class_;
			static INode::Ptr lengthNode_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ARRAY_OBJECT_H */