#include "IndexObject.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto target = dynamic_cast<IIndexTarget *>(memory_->object()->base());
	if (target == nullptr)
		return nullptr;//TODO: Throw exception

	return target->getIndexValue(value_);
}

bool StructuredScript::Objects::IndexObject::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto target = dynamic_cast<IIndexTarget *>(memory_->object()->base());
	if (target == nullptr)
		return nullptr;//TODO: Throw exception

	return target->getIndexValue(value_)->truth(storage, exception, expr);
}

std::string StructuredScript::Objects::IndexObject::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto target = dynamic_cast<IIndexTarget *>(memory_->object()->base());
	if (target == nullptr)
		return nullptr;//TODO: Throw exception

	return target->getIndexValue(value_)->str(storage, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	auto target = dynamic_cast<IIndexTarget *>(memory_->object()->base());
	if (target == nullptr)
		return nullptr;//TODO: Throw exception

	auto indexValue = target->getIndexValue(value_);
	return dynamic_cast<IPrimitiveObject *>(indexValue->base())->evaluateLeftUnary(value, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	auto target = dynamic_cast<IIndexTarget *>(memory_->object()->base());
	if (target == nullptr)
		return nullptr;//TODO: Throw exception

	auto indexValue = target->getIndexValue(value_);
	return dynamic_cast<IPrimitiveObject *>(indexValue->base())->evaluateRightUnary(value, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::evaluateBinary(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	auto target = dynamic_cast<IIndexTarget *>(memory_->object()->base());
	if (target == nullptr)
		return nullptr;//TODO: Throw exception

	auto indexValue = target->getIndexValue(value_);
	return dynamic_cast<IPrimitiveObject *>(indexValue->base())->evaluateBinary(value, right, storage, exception, expr);
}

int StructuredScript::Objects::IndexObject::rank(){
	auto target = dynamic_cast<IIndexTarget *>(memory_->object()->base());
	if (target == nullptr)
		return -1;

	auto indexValue = target->getIndexValue(value_);
	return dynamic_cast<IPrimitiveObject *>(indexValue->base())->rank();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::promote_(Primitive *target){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::IndexObject::evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::IndexObject::evaluate_(const std::string &value, INumber *right, IExceptionManager *exception, INode *expr){
	return nullptr;
}
