#pragma once

#ifndef STRUCTURED_SCRIPT_INDEX_OBJECT_H
#define STRUCTURED_SCRIPT_INDEX_OBJECT_H

#include "Primitive.h"

namespace StructuredScript{
	namespace Objects{
		class IndexObject : public Primitive, public IIndexObject{
		public:
			IndexObject(IType::Ptr type, unsigned int value, IMemory *target)
				: Primitive(type), value_(value), target_(target){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual int rank() override;

		protected:
			virtual Ptr promote_(Primitive *target) override;

			virtual IAny::Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr evaluate_(const std::string &value, INumber *right, IExceptionManager *exception, INode *expr);

			unsigned int value_;
			IMemory *target_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_INDEX_OBJECT_H */