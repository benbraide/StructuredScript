#include "IndexObject.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto objectBase = memory_->object()->base();
	auto target = dynamic_cast<IIndexTarget *>(objectBase.get());
	if (target == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Bad index object while copying!", expr)));
	}

	return target->getIndexValue(value_);
}

bool StructuredScript::Objects::IndexObject::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto objectBase = memory_->object()->base();
	auto target = dynamic_cast<IIndexTarget *>(objectBase.get());
	if (target == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Bad index object while converting to bool!", expr)));

		return false;
	}

	return target->getIndexValue(value_)->truth(storage, exception, expr);
}

std::string StructuredScript::Objects::IndexObject::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto objectBase = memory_->object()->base();
	auto target = dynamic_cast<IIndexTarget *>(objectBase.get());
	if (target == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Bad index object while converting to string!", expr)));

		return "";
	}

	return target->getIndexValue(value_)->str(storage, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	auto objectBase = memory_->object()->base();
	auto target = dynamic_cast<IIndexTarget *>(objectBase.get());
	if (target == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Bad index object!", expr)));
	}

	auto indexValue = target->getIndexValue(value_)->base();
	return dynamic_cast<IPrimitiveObject *>(indexValue.get())->evaluateLeftUnary(value, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	auto objectBase = memory_->object()->base();
	auto target = dynamic_cast<IIndexTarget *>(objectBase.get());
	if (target == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Bad index object!", expr)));
	}

	auto indexValue = target->getIndexValue(value_)->base();
	return dynamic_cast<IPrimitiveObject *>(indexValue.get())->evaluateRightUnary(value, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::IndexObject::evaluateBinary(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	auto objectBase = memory_->object()->base();
	auto target = dynamic_cast<IIndexTarget *>(objectBase.get());
	if (target == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Bad index object!", expr)));
	}

	auto indexValue = target->getIndexValue(value_)->base();
	return dynamic_cast<IPrimitiveObject *>(indexValue.get())->evaluateBinary(value, right, storage, exception, expr);
}

int StructuredScript::Objects::IndexObject::rank(){
	auto objectBase = memory_->object()->base();
	auto target = dynamic_cast<IIndexTarget *>(objectBase.get());
	if (target == nullptr)
		return -1;

	auto indexValue = target->getIndexValue(value_)->base();
	return dynamic_cast<IPrimitiveObject *>(indexValue.get())->rank();
}
