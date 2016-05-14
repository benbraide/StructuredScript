#include "SpecializedStorage.h"

StructuredScript::Storage::SharedStorage::Ptr *StructuredScript::Storage::SharedStorage::addStorage(const std::string &name){
	return first_->addStorage(name);
}

StructuredScript::IStorage *StructuredScript::Storage::SharedStorage::findStorage(const std::string &name, bool localOnly){
	auto value = first_->findStorage(name, true);
	return (value == nullptr) ? then_->findStorage(name, localOnly) : value;
}

StructuredScript::IType::Ptr *StructuredScript::Storage::SharedStorage::addType(const std::string &name){
	return (then_->findType(name, true) == nullptr) ? first_->addType(name) : nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Storage::SharedStorage::findType(const std::string &name, bool localOnly){
	auto value = first_->findType(name, true);
	return (value == nullptr) ? then_->findType(name, localOnly) : value;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::SharedStorage::addMemory(const std::string &name){
	auto object = then_->findMemory(name, true);
	return (object == nullptr || dynamic_cast<IFunctionMemory *>(object.get()) != nullptr) ? first_->addMemory(name) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findMemory(const std::string &name, bool localOnly){
	auto value = first_->findMemory(name, true);
	return (value == nullptr) ? then_->findMemory(name, localOnly) : value;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findFunctionMemory(const std::string &name, bool localOnly){
	auto value = first_->findFunctionMemory(name, true);
	return (value == nullptr) ? then_->findFunctionMemory(name, localOnly) : value;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::SharedStorage::addOperatorMemory(const std::string &name){
	auto object = then_->findOperatorMemory(name, true);
	return (object == nullptr || dynamic_cast<IFunctionMemory *>(object.get()) != nullptr) ? first_->addOperatorMemory(name) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findOperatorMemory(const std::string &name, bool localOnly){
	auto value = first_->findOperatorMemory(name, true);
	return (value == nullptr) ? then_->findOperatorMemory(name, localOnly) : value;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::SharedStorage::addTypenameOperatorMemory(const std::string &name){
	auto object = then_->findTypenameOperatorMemory(name, true);
	return (object == nullptr || dynamic_cast<IFunctionMemory *>(object.get()) != nullptr) ? first_->addTypenameOperatorMemory(name) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::SharedStorage::findTypenameOperatorMemory(const std::string &name, bool localOnly){
	auto value = first_->findTypenameOperatorMemory(name, true);
	return (value == nullptr) ? then_->findTypenameOperatorMemory(name, localOnly) : value;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Storage::SharedStorage::addMemoryAttribute(const std::string &name){
	return first_->addMemoryAttribute(name);
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::SharedStorage::findMemoryAttribute(const std::string &name, bool localOnly){
	auto value = first_->findMemoryAttribute(name, true);
	return (value == nullptr) ? then_->findMemoryAttribute(name, localOnly) : value;
}

bool StructuredScript::Storage::SharedStorage::remove(IMemory::Ptr target){
	return first_->remove(target);
}
