#pragma once

#ifndef STRUCTURED_SCRIPT_NAN_OBJECT_H
#define STRUCTURED_SCRIPT_NAN_OBJECT_H

#include "Primitive.h"

#include "../Common/Factory.h"
#include "../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	namespace Objects{
		class NaN : public Primitive, public INumber, public IInteger, public IReal, public INaN{
		public:
			NaN()
				: Primitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_NAN)){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr) override;

			virtual int rank() override;

		protected:
			virtual Ptr promote_(Primitive *target) override;

			virtual IAny::Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override;

			virtual IAny::Ptr evaluate_(const std::string &value, INumber *right, IExceptionManager *exception, INode *expr);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NAN_OBJECT_H */