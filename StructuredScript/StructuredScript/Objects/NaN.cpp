#include "NaN.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::NaN::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<NaN>();
}

bool StructuredScript::Objects::NaN::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

std::string StructuredScript::Objects::NaN::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "NaN";
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::NaN::evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (value == "+" || value == "-" || value == "~")
		return std::make_shared<NaN>();

	if (value == "++" || value == "--")
		return (memory_ == nullptr) ? nullptr : std::make_shared<NaN>();

	return Primitive::evaluateLeftUnary(value, storage, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::NaN::evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (value == "++" || value == "--")
		return (memory_ == nullptr) ? nullptr : std::make_shared<NaN>();

	return Primitive::evaluateRightUnary(value, storage, exception, expr);
}

int StructuredScript::Objects::NaN::rank(){
	return Primitive::NAN_RANK;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::NaN::promote_(Primitive *target){
	return target->ptr();
}

StructuredScript::IAny::Ptr StructuredScript::Objects::NaN::evaluate_(const std::string &value, INumber *right, IExceptionManager *exception, INode *expr){
	if (value == "<" || value == ">")
		return PrimitiveFactory::createBool(false);

	if (value == "<=" || value == ">=" || value == "==")
		return PrimitiveFactory::createBool(dynamic_cast<NaN *>(right) != nullptr);

	if (value == "!=")
		return PrimitiveFactory::createBool(dynamic_cast<NaN *>(right) == nullptr);

	if (value == "+" || value == "-" || value == "*" || value == "**" || value == "/")
		return std::make_shared<NaN>();

	if (value == "%" || value == "|" || value == "&" || value == "^" || value == "<<" || value == ">>"){
		return (dynamic_cast<IInteger *>(right) == nullptr) ? nullptr : std::make_shared<NaN>();
	}

	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::NaN::evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr){
	auto number = dynamic_cast<INumber *>(right.get());
	if (number == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Operands mismatch!", expr)));
	}

	return evaluate_(value, number, exception, expr);
}
