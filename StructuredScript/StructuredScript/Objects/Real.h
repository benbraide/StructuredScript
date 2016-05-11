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

			explicit Real(const ValueType &value)
				: BaseType(value){}

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override{
				if (value == "+")
					return std::make_shared<ObjectType>(value_);

				if (value == "-")
					return std::make_shared<ObjectType>(-value_);

				return BaseType::evaluateLeftUnary(value, exception, expr);
			}

		protected:
			virtual IAny::Ptr evaluate_(const std::string &value, Number *left, Number *right, IExceptionManager *exception, INode *expr){
				if (value == "**")
					return std::make_shared<ObjectType>(std::pow(left->value(), right->value()));

				return BaseType::evaluate_(value, left, right, exception, expr);
			}

			std::string str_(int precision){
				std::ostringstream ss;

				ss << std::fixed << std::setprecision(precision);
				ss << value_;

				auto value = ss.str();
				if (value.find('e') < value.size())
					return value;

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
			explicit Float(float value)
				: Real(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return str_(6);
			}
		};

		class Double : public Real<Double, double, Primitive::DOUBLE_RANK> {
		public:
			explicit Double(double value)
				: Real(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return str_(12);
			}
		};

		class LDouble : public Real<LDouble, long double, Primitive::LDOUBLE_RANK> {
		public:
			explicit LDouble(long double value)
				: Real(value){}

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override{
				return str_(24);
			}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_REAL_OBJECT_H */