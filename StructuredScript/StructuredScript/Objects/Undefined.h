#pragma once

#ifndef STRUCTURED_SCRIPT_UNDEFINED_OBJECT_H
#define STRUCTURED_SCRIPT_UNDEFINED_OBJECT_H

#include "Primitive.h"

namespace StructuredScript{
	namespace Objects{
		class Undefined : public Primitive, public INumber, public IInteger, public IReal, public INaN{
		public:
			Undefined()
				: Primitive(nullptr){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IType::Ptr type() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual int rank() override;

		protected:
			virtual Ptr promote_(Primitive *target) override;

			virtual IAny::Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr evaluate_(const std::string &value, INumber *right, IExceptionManager *exception, INode *expr);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_UNDEFINED_OBJECT_H */