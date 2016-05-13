#include "Storage.h"

StructuredScript::Storage::Storage::Ptr *StructuredScript::Storage::Storage::addStorage(const std::string &name){
	return &storages_[name];
}

StructuredScript::IStorage *StructuredScript::Storage::Storage::findStorage(const std::string &name, bool localOnly){
	auto storage = storages_.find(name);
	if (storage != storages_.end())
		return storage->second.get();

	auto type = findType(name, true);
	if (type != nullptr)
		return dynamic_cast<IStorage *>(type.get());

	return (localOnly || parent_ == nullptr) ? nullptr : parent_->findStorage(name, false);
}

StructuredScript::IType::Ptr *StructuredScript::Storage::Storage::addType(const std::string &name){
	return (findType(name, true) == nullptr) ? &types_[name] : nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Storage::Storage::findType(const std::string &name, bool localOnly){
	auto type = types_.find(name);
	if (type != types_.end())
		return type->second;

	return (localOnly || parent_ == nullptr) ? nullptr : parent_->findType(name, false);
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::Storage::addMemory(const std::string &name){
	auto object = objects_.find(name);
	if (object != objects_.end())//Check if it is a function memory
		return (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr) ? nullptr : &object->second;

	return &objects_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findMemory(const std::string &name, bool localOnly){
	auto object = objects_.find(name);
	if (object != objects_.end())
		return object->second;

	auto type = findType(name, true);
	if (type != nullptr){//Create type object in a temporary memory
		return std::make_shared<Memory>(this, IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_TYPE),
			PrimitiveFactory::createTypeObject(type), nullptr);
	}

	return (localOnly || parent_ == nullptr) ? nullptr : parent_->findMemory(name, false);
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::Storage::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findOperatorMemory(const std::string &name, bool localOnly){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::Storage::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findTypenameOperatorMemory(const std::string &name, bool localOnly){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Storage::Storage::addMemoryAttribute(const std::string &name){
	return (findMemoryAttribute(name, true) == nullptr) ? &attributes_[name] : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::Storage::findMemoryAttribute(const std::string &name, bool localOnly){
	auto attribute = attributes_.find(name);
	if (attribute != attributes_.end())
		return attribute->second;

	return (localOnly || parent_ == nullptr) ? nullptr : parent_->findMemoryAttribute(name, false);
}

bool StructuredScript::Storage::Storage::remove(IMemory::Ptr target){
	for (auto object = objects_.begin(); object != objects_.end(); ++object){
		if (object->second == target){
			objects_.erase(object);
			return true;
		}
	}

	return false;
}
