#include "SpecializedStorage.h"

StructuredScript::IStorage *StructuredScript::Storage::SharedStorage::parent(){
	return then_;
}

StructuredScript::Storage::SharedStorage::Ptr *StructuredScript::Storage::SharedStorage::addStorage(const std::string &name){
	return first_->addStorage(name);
}

StructuredScript::IStorage *StructuredScript::Storage::SharedStorage::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto value = first_->findStorage(name, SEARCH_LOCAL);
	return (value == nullptr) ? then_->findStorage(name, searchScope) : value;
}

StructuredScript::IType::Ptr *StructuredScript::Storage::SharedStorage::addType(const std::string &name){
	return (then_->findType(name, SEARCH_LOCAL) == nullptr) ? first_->addType(name) : nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Storage::SharedStorage::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto value = first_->findType(name, SEARCH_LOCAL);
	return (value == nullptr) ? then_->findType(name, searchScope) : value;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::SharedStorage::addMemory(const std::string &name){
	auto object = then_->findMemory(name, SEARCH_LOCAL);
	return (object == nullptr || dynamic_cast<IFunctionMemory *>(object.get()) != nullptr) ? first_->addMemory(name) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto value = first_->findMemory(name, SEARCH_LOCAL);
	return (value == nullptr) ? then_->findMemory(name, searchScope) : value;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto value = first_->findFunctionMemory(name, SEARCH_LOCAL);
	return (value == nullptr) ? then_->findFunctionMemory(name, searchScope) : value;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::SharedStorage::addOperatorMemory(const std::string &name){
	auto object = then_->findOperatorMemory(name, SEARCH_LOCAL);
	return (object == nullptr || dynamic_cast<IFunctionMemory *>(object.get()) != nullptr) ? first_->addOperatorMemory(name) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto value = first_->findOperatorMemory(name, SEARCH_LOCAL);
	return (value == nullptr) ? then_->findOperatorMemory(name, searchScope) : value;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::SharedStorage::addTypenameOperatorMemory(const std::string &name){
	auto object = then_->findTypenameOperatorMemory(name, SEARCH_LOCAL);
	return (object == nullptr || dynamic_cast<IFunctionMemory *>(object.get()) != nullptr) ? first_->addTypenameOperatorMemory(name) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findTypenameOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto value = first_->findTypenameOperatorMemory(name, SEARCH_LOCAL);
	return (value == nullptr) ? then_->findTypenameOperatorMemory(name, searchScope) : value;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Storage::SharedStorage::addMemoryAttribute(const std::string &name){
	return first_->addMemoryAttribute(name);
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::SharedStorage::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto value = first_->findMemoryAttribute(name, SEARCH_LOCAL);
	return (value == nullptr) ? then_->findMemoryAttribute(name, searchScope) : value;
}

StructuredScript::Storage::SharedStorage::ExternalCallType StructuredScript::Storage::SharedStorage::findExternalCall(const std::string &name){
	auto value = first_->findExternalCall(name);
	return (value == nullptr) ? then_->findExternalCall(name) : value;
}

bool StructuredScript::Storage::SharedStorage::remove(IMemory::Ptr target){
	return first_->remove(target);
}
