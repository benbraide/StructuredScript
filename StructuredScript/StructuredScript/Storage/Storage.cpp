#include "Storage.h"

StructuredScript::IStorage *StructuredScript::Storage::Storage::parent(){
	return parent_;
}

StructuredScript::Storage::Storage::Ptr *StructuredScript::Storage::Storage::addStorage(const std::string &name){
	if (findType(name, IStorage::SEARCH_LOCAL) != nullptr || findMemory(name, IStorage::SEARCH_LOCAL) != nullptr)
		return nullptr;

	return &storages_[name];
}

StructuredScript::IStorage *StructuredScript::Storage::Storage::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto storage = storages_.find(name);
	if (storage != storages_.end())
		return storage->second.get();

	auto type = findType(name, IStorage::SEARCH_LOCAL);
	if (type != nullptr)
		return dynamic_cast<IStorage *>(type.get());

	return (searchScope != IStorage::SEARCH_DEFAULT || parent_ == nullptr) ? nullptr : parent_->findStorage(name, IStorage::SEARCH_DEFAULT);
}

StructuredScript::IType::Ptr *StructuredScript::Storage::Storage::addType(const std::string &name){
	if (findStorage(name, IStorage::SEARCH_LOCAL) != nullptr || findType(name, IStorage::SEARCH_LOCAL) != nullptr || findMemory(name, IStorage::SEARCH_LOCAL) != nullptr)
		return nullptr;

	return &types_[name];
}

StructuredScript::IType::Ptr StructuredScript::Storage::Storage::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto type = types_.find(name);
	if (type != types_.end())
		return type->second;

	return (searchScope != IStorage::SEARCH_DEFAULT || parent_ == nullptr) ? nullptr : parent_->findType(name, IStorage::SEARCH_DEFAULT);
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::Storage::addMemory(const std::string &name){
	if (findStorage(name, IStorage::SEARCH_LOCAL) != nullptr || findType(name, IStorage::SEARCH_LOCAL) != nullptr)
		return nullptr;

	auto object = objects_.find(name);
	if (object != objects_.end())//Check if it is a function memory
		return (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr) ? nullptr : &object->second;

	return &objects_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto object = objects_.find(name);
	if (object != objects_.end()){
		if (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr)
			return object->second;

		std::list<IMemory::Ptr> list({ object->second });
		if (searchScope == IStorage::SEARCH_DEFAULT && parent_ != nullptr){//Get all functions with same name
			auto memory = parent_->findFunctionMemory(name, IStorage::SEARCH_DEFAULT);
			if (memory != nullptr)
				list.push_back(memory);
		}

		return std::make_shared<FunctionMemory>(list);
	}

	auto type = findType(name, IStorage::SEARCH_LOCAL);
	if (type != nullptr){//Create type object in a temporary memory
		return std::make_shared<Memory>(this, IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_TYPE),
			PrimitiveFactory::createTypeObject(type), nullptr);
	}

	return (searchScope != IStorage::SEARCH_DEFAULT || parent_ == nullptr) ? nullptr : parent_->findMemory(name, IStorage::SEARCH_DEFAULT);
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	std::list<IMemory::Ptr> list;

	auto object = objects_.find(name);
	if (object != objects_.end() && dynamic_cast<IFunctionMemory *>(object->second.get()) != nullptr)
		list.push_back(object->second);

	if (searchScope == IStorage::SEARCH_DEFAULT && parent_ != nullptr){//Get all functions with same name
		auto memory = parent_->findFunctionMemory(name, IStorage::SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back(memory);
	}

	return list.empty() ? nullptr : std::make_shared<FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::Storage::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Storage::Storage::addTypenameOperatorMemory(IType::Ptr name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Storage::Storage::addMemoryAttribute(const std::string &name){
	return (findMemoryAttribute(name, IStorage::SEARCH_LOCAL) == nullptr) ? &attributes_[name] : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::Storage::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto attribute = attributes_.find(name);
	if (attribute != attributes_.end())
		return attribute->second;

	return (searchScope != IStorage::SEARCH_DEFAULT || parent_ == nullptr) ? nullptr : parent_->findMemoryAttribute(name, IStorage::SEARCH_DEFAULT);
}

StructuredScript::IStorage::ExternalCallType StructuredScript::Storage::Storage::findExternalCall(const std::string &name){
	return nullptr;
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

bool StructuredScript::Storage::Storage::use(IStorage *storage){
	if (storage != this && std::find(usedStorages_.begin(), usedStorages_.end(), storage) == usedStorages_.end())
		usedStorages_.push_back(storage);

	return true;
}

bool StructuredScript::Storage::Storage::use(const std::string &name, IMemory::Ptr value){
	return true;
}
