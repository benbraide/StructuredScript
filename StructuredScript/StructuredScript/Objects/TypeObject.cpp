#include "TypeObject.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<TypeObject>(value_);
}

StructuredScript::IAny *StructuredScript::Objects::TypeObject::base(){
	return this;
}

std::string StructuredScript::Objects::TypeObject::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_->name();
}

int StructuredScript::Objects::TypeObject::rank(){
	return -1;
}

StructuredScript::IType::Ptr StructuredScript::Objects::TypeObject::value(){
	return value_;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::promote_(Primitive *target){
	return nullptr;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::TypeObject::evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr){
	auto alike = dynamic_cast<TypeObject *>(right->base());
	if (alike != nullptr){
		if (value == "==" || value == "<=" || value == ">=")
			return PrimitiveFactory::createBool(value_->isEqual(alike->value_));

		if (value == "!=")
			return PrimitiveFactory::createBool(!value_->isEqual(alike->value_));
	}

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}
