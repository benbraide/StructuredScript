#include "PrimitiveObject.h"

StructuredScript::IStorage *StructuredScript::Objects::PrimitiveObject::parent(){
	if (type_ == nullptr)
		return (memory_ == nullptr) ? nullptr : memory_->storage();

	return type_->storage();
}

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Objects::PrimitiveObject::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Objects::PrimitiveObject::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == type_->name())
		return this;

	return (searchScope == SEARCH_DEFAULT) ? dynamic_cast<IStorage *>(type_.get())->findStorage(name) : nullptr;
}

StructuredScript::IType::Ptr *StructuredScript::Objects::PrimitiveObject::addType(const std::string &name){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::PrimitiveObject::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return (searchScope == SEARCH_DEFAULT) ? dynamic_cast<IStorage *>(type_.get())->findType(name) : nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::PrimitiveObject::addMemory(const std::string &name){
	auto object = objects_.find(name);
	return (object == objects_.end()) ? &objects_[name] : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::PrimitiveObject::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto object = objects_.find(name);
	if (object != objects_.end())
		return object->second;

	auto memory = dynamic_cast<IStorage *>(type_.get())->findMemory(name, searchScope);
	auto functionMemory = dynamic_cast<IFunctionMemory *>(memory.get());
	if (functionMemory != nullptr)//Set object as storage
		functionMemory->setStorage(this);

	return memory;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::PrimitiveObject::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto memory = dynamic_cast<IStorage *>(type_.get())->findFunctionMemory(name, searchScope);
	if (memory != nullptr)//Set object as storage
		dynamic_cast<IFunctionMemory *>(memory.get())->setStorage(this);

	return memory;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::PrimitiveObject::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::PrimitiveObject::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto memory = dynamic_cast<IStorage *>(type_.get())->findOperatorMemory(name, searchScope);
	if (memory != nullptr)//Set object as storage
		dynamic_cast<IFunctionMemory *>(memory.get())->setStorage(this);

	return memory;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::PrimitiveObject::addTypenameOperatorMemory(IType::Ptr name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::PrimitiveObject::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto memory = dynamic_cast<IStorage *>(type_.get())->findTypenameOperatorMemory(name, searchScope);
	if (memory != nullptr)//Set object as storage
		dynamic_cast<IFunctionMemory *>(memory.get())->setStorage(this);

	return memory;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::PrimitiveObject::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::PrimitiveObject::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::Interfaces::Storage::ExternalCallType StructuredScript::Objects::PrimitiveObject::findExternalCall(const std::string &name){
	return dynamic_cast<IStorage *>(type_.get())->findExternalCall(name);
}

bool StructuredScript::Objects::PrimitiveObject::remove(IMemory::Ptr target){
	return false;
}
