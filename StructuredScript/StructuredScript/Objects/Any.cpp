#include "Any.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Any::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Any::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot copy object!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Any::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	return type->isEqual(type_) ? ptr() : nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Any::base(){
	return shared_from_this();
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Any::assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Any::evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Any::evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Any::evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Any::type(){
	return type_;
}

void StructuredScript::Objects::Any::setMemory(IMemory *memory){
	memory_ = memory;
}

StructuredScript::IMemory *StructuredScript::Objects::Any::memory(){
	return memory_;
}

bool StructuredScript::Objects::Any::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot get truth value of object!", expr)));

	return false;
}

std::string StructuredScript::Objects::Any::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot get string value of object!", expr)));

	return "";
}

StructuredScript::IStorage *StructuredScript::Objects::Any::parent(){
	if (type_ == nullptr)
		return (memory_ == nullptr) ? nullptr : memory_->storage();

	return type_->storage();
}

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Objects::Any::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Objects::Any::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == type_->name())
		return this;

	auto storage = dynamic_cast<IStorage *>(type_.get());
	return (storage == nullptr) ? nullptr : storage->findStorage(name, searchScope);
}

StructuredScript::IType::Ptr *StructuredScript::Objects::Any::addType(const std::string &name){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Any::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto storage = dynamic_cast<IStorage *>(type_.get());
	return (storage == nullptr) ? nullptr : storage->findType(name, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Any::addMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberMemory(name, searchScope);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberFunctionMemory(name, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Any::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberOperatorMemory(name, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Any::addTypenameOperatorMemory(IType::Ptr name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberTypenameOperatorMemory(name, searchScope);
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::Any::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::Any::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::Objects::Any::ExternalCallType StructuredScript::Objects::Any::findExternalCall(const std::string &name){
	auto storage = dynamic_cast<IStorage *>(type_.get());
	return (storage == nullptr) ? nullptr : storage->findExternalCall(name);
}

bool StructuredScript::Objects::Any::remove(IMemory::Ptr target){
	return false;
}
