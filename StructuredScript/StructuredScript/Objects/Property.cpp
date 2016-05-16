#include "Property.h"

StructuredScript::Objects::Property::Property(IType::Ptr type)
	: Any(type){
	auto compoundType = dynamic_cast<ICompoundType *>(type.get());
	if (compoundType != nullptr){
		getMemory_("get", compoundType, get_);
		getMemory_("set", compoundType, set_);
	}
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
	return (get_ == nullptr) ? nullptr : get_->call({}, memory_->storage(), &xManager, nullptr);
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

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Objects::Property::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Objects::Property::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto storage = dynamic_cast<IStorage *>(type_.get());
	if (storage != nullptr){
		auto value = storage->findStorage(name, SEARCH_FAMILY);
		if (value != nullptr)
			return value;
	}

	return (searchScope == SEARCH_DEFAULT) ? memory_->storage()->findStorage(name, searchScope) : nullptr;
}

StructuredScript::IType::Ptr *StructuredScript::Objects::Property::addType(const std::string &name){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Property::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto storage = dynamic_cast<IStorage *>(type_.get());
	if (storage != nullptr){
		auto value = storage->findType(name, SEARCH_FAMILY);
		if (value != nullptr)
			return value;
	}

	return (searchScope == SEARCH_DEFAULT) ? memory_->storage()->findType(name, searchScope) : nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Property::addMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Property::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	if (compoundType != nullptr){
		auto value = compoundType->findMemberMemory(name, SEARCH_FAMILY);
		if (value != nullptr)
			return value;
	}

	return (searchScope == SEARCH_DEFAULT) ? memory_->storage()->findMemory(name, searchScope) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Property::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	if (compoundType != nullptr){
		auto value = compoundType->findMemberFunctionMemory(name, SEARCH_FAMILY);
		if (value != nullptr)
			return value;
	}

	return (searchScope == SEARCH_DEFAULT) ? memory_->storage()->findFunctionMemory(name, searchScope) : nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Property::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Property::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	if (compoundType != nullptr){
		auto value = compoundType->findMemberOperatorMemory(name, SEARCH_FAMILY);
		if (value != nullptr)
			return value;
	}

	return (searchScope == SEARCH_DEFAULT) ? memory_->storage()->findOperatorMemory(name, searchScope) : nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Property::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Property::findTypenameOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	if (compoundType != nullptr){
		auto value = compoundType->findMemberTypenameOperatorMemory(name, SEARCH_FAMILY);
		if (value != nullptr)
			return value;
	}

	return (searchScope == SEARCH_DEFAULT) ? memory_->storage()->findTypenameOperatorMemory(name, searchScope) : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::Property::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::Property::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::Objects::Property::ExternalCallType StructuredScript::Objects::Property::findExternalCall(const std::string &name){
	return memory_->storage()->findExternalCall(name);
}

bool StructuredScript::Objects::Property::remove(IMemory::Ptr target){
	return false;
}

void StructuredScript::Objects::Property::getMemory_(const std::string &name, ICompoundType *type, IFunction *&target){
	auto memory = type->findMemberFunctionMemory(name, SEARCH_LOCAL);
	auto functionMemory = dynamic_cast<IFunctionMemory *>(memory.get());
	if (functionMemory == nullptr)
		return;

	auto function = functionMemory->first();
	if (function != nullptr)
		target = dynamic_cast<IFunction *>(function->object().get());
}
