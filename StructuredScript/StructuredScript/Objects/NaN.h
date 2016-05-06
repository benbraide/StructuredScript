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

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return std::make_shared<NaN>();
			}

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return false;
			}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return "NaN";
			}

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override{
				if (value == "~")
					return std::make_shared<NaN>();

				if (value == "++" || value == "--")
					return (memory_ == nullptr) ? nullptr : std::make_shared<NaN>();

				return Primitive::evaluateLeftUnary(value, exception, expr);
			}

			virtual Ptr evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr) override{
				if (value == "++" || value == "--")
					return (memory_ == nullptr) ? nullptr : std::make_shared<NaN>();

				return Primitive::evaluateRightUnary(value, exception, expr);
			}

			virtual int rank() override{
				return -1;
			}

		protected:
			virtual Ptr promote_(Primitive *target) override{
				return nullptr;
			}

			virtual IAny::Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr) override{
				auto number = dynamic_cast<INumber *>(right.get());
				if (number == nullptr)
					return nullptr;//TODO: Throw exception

				return evaluate_(value, number, exception, expr);
			}

			virtual IAny::Ptr evaluate_(const std::string &value, INumber *right, IExceptionManager *exception, INode *expr){
				if (value == "<" || value == ">")
					return PrimitiveFactory::createBool(false);

				if (value == "<=" || value == ">=" || value == "==")
					return PrimitiveFactory::createBool(dynamic_cast<NaN *>(right) != nullptr);

				if (value == "!=")
					return PrimitiveFactory::createBool(dynamic_cast<NaN *>(right) == nullptr);

				if (value == "+" || value == "-" || value == "*" || value == "/")
					return std::make_shared<NaN>();

				if (value == "%" || value == "|" || value == "&" || value == "^" || value == "<<" || value == ">>"){
					return (dynamic_cast<IInteger *>(right) == nullptr) ? nullptr : std::make_shared<NaN>();
				}

				return nullptr;
			}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NAN_OBJECT_H */