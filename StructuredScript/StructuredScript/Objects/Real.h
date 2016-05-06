#pragma once

#ifndef STRUCTURED_SCRIPT_REAL_OBJECT_H
#define STRUCTURED_SCRIPT_REAL_OBJECT_H

#include <sstream>
#include <iomanip>

#include "Number.h"

namespace StructuredScript{
	namespace Objects{
		template <class ObjectType, class ValueType, unsigned short Rank>
		class Real : public Number<ObjectType, ValueType, Rank>, public IReal{
		public:
			typedef Number<ObjectType, ValueType, Rank> BaseType;

			Real(const ValueType &value)
				: BaseType(value){}

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override{
				if (value == "+")
					return std::make_shared<ObjectType>(value_);

				if (value == "-")
					return std::make_shared<ObjectType>(-value_);

				return BaseType::evaluateLeftUnary(value, exception, expr);
			}

		protected:
			std::string str_(int precision){
				std::ostringstream ss;

				ss << std::setprecision(precision);
				ss << value_;

				auto value = ss.str();
				if (value.find('.') >= value.size())//Append decimal point and zero
					return (value + ".0");

				while (!value.empty() && *value.rbegin() == '0')//Truncate trailing zeroes
					value.erase(value.size() - 1);

				if (!value.empty() && *value.rbegin() == '.')//Append zero immediately after decimal point
					return (value + "0");

				return value;
			}
		};

		class Float : public Real<Float, float, Primitive::FLOAT_RANK> {
		public:
			Float(float value)
				: Real(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return str_(6);
			}
		};

		class Double : public Real<Double, double, Primitive::DOUBLE_RANK> {
		public:
			Double(double value)
				: Real(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return str_(12);
			}
		};

		class LDouble : public Real<LDouble, long double, Primitive::LDOUBLE_RANK> {
		public:
			LDouble(long double value)
				: Real(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return str_(24);
			}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_REAL_OBJECT_H */