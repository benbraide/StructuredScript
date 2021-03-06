#include "TypeObject.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<TypeObject>(value_);
}

std::string StructuredScript::Objects::TypeObject::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return (value_ == nullptr) ? Primitive::str(storage, exception, expr) : value_->name();
}

StructuredScript::IType::Ptr StructuredScript::Objects::TypeObject::value(){
	return value_;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr){
	if (value_ == nullptr)
		return Primitive::evaluate_(value, reversed, right, exception, expr);

	auto rightBase = right->base();
	auto alike = dynamic_cast<TypeObject *>(rightBase.get());
	if (alike != nullptr){
		if (value == "==" || value == "<=" || value == ">=")
			return PrimitiveFactory::createBool(value_->isEqual(alike->value_));

		if (value == "!=")
			return PrimitiveFactory::createBool(!value_->isEqual(alike->value_));
	}

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}
