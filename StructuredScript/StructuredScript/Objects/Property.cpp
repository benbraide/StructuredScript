#include "Property.h"

StructuredScript::Objects::Property::Property(IType::Ptr type)
	: Any(type){
	auto storage = dynamic_cast<IStorage *>(type.get());
	getMemory_("get", storage, get_);
	getMemory_("set", storage, set_);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Property::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto target = base();
	if (target == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Property has no getter!", expr)));
	}

	return (target->memory() == nullptr) ? target :  target->clone(storage, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Property::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	auto target = base();
	if (target == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Property has no getter!", expr)));
	}

	return target->cast(type, storage, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Property::base(){
	ExceptionManager xManager;
	return (get_ == nullptr) ? nullptr : get_->call(false, {}, &xManager, nullptr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Property::assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (set_ == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Property has no setter!", expr)));
	}

	if (value.size() > 1u){//Compound assignment
		auto left = base();
		if (left == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Property has no getter!", expr)));
		}

		right = left->evaluateBinary(value.substr(0, value.size() - 1), right, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	return set_->call(false, IFunction::ArgListType{ right }, exception, expr);
}

StructuredScript::IType::Ptr StructuredScript::Objects::Property::type(){
	auto target = base();
	return (target == nullptr) ? nullptr : target->type();
}

bool StructuredScript::Objects::Property::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto target = base();
	if (target == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Property has no getter!", expr)));

		return false;
	}

	return target->truth(storage, exception, expr);
}

std::string StructuredScript::Objects::Property::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto target = base();
	if (target == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Property has no getter!", expr)));

		return "";
	}

	return target->str(storage, exception, expr);
}

bool StructuredScript::Objects::Property::remove(IMemory::Ptr target){
	return false;
}

void StructuredScript::Objects::Property::getMemory_(const std::string &name, IStorage *storage, FunctionMemoryType &target){
	auto memory = storage->findFunctionMemory(name, SEARCH_LOCAL);
	if (memory != nullptr)
		target = std::dynamic_pointer_cast<IFunctionMemory>(memory);
}
