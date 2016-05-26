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

	for (auto item : usedStorages_){
		auto storage = item->findStorage(name, IStorage::SEARCH_LOCAL);
		if (storage != nullptr)
			return storage;
	}

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

	type = usedTypes_.find(name);
	if (type != usedTypes_.end())
		return type->second;

	for (auto item : usedStorages_){
		auto type = item->findType(name, IStorage::SEARCH_LOCAL);
		if (type != nullptr)
			return type;
	}

	return (searchScope != IStorage::SEARCH_DEFAULT || parent_ == nullptr) ? nullptr : parent_->findType(name, IStorage::SEARCH_DEFAULT);
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Storage::Storage::addMemory(const std::string &name){
	if (findStorage(name, IStorage::SEARCH_LOCAL) != nullptr || findType(name, IStorage::SEARCH_LOCAL) != nullptr)
		return nullptr;

	auto object = objects_.find(name);
	if (object != objects_.end())//Check if it is a function memory
		return (dynamic_cast<IFunctionMemory *>(object->second.memory.get()) == nullptr) ? nullptr : &object->second;

	return &objects_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto object = objects_.find(name);
	if (object != objects_.end()){
		if (dynamic_cast<IFunctionMemory *>(object->second.memory.get()) == nullptr)
			return object->second.memory;

		FunctionMemory::ListType list({ object->second });
		auto object = usedObjects_.find(name);
		if (object != usedObjects_.end() && dynamic_cast<IFunctionMemory *>(object->second.get()) != nullptr)
			list.push_back({ object->second, nullptr });

		for (auto item : usedStorages_){
			auto memory = item->findFunctionMemory(name, IStorage::SEARCH_LOCAL);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}

		if (searchScope == IStorage::SEARCH_DEFAULT && parent_ != nullptr){//Get all functions with same name
			auto memory = parent_->findFunctionMemory(name, IStorage::SEARCH_DEFAULT);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}

		return std::make_shared<FunctionMemory>(list);
	}

	auto usedObject = usedObjects_.find(name);
	if (usedObject != usedObjects_.end())
		return usedObject->second;

	for (auto item : usedStorages_){
		auto memory = item->findMemory(name, IStorage::SEARCH_LOCAL);
		if (memory != nullptr)
			return memory;
	}

	if (findType(name, IStorage::SEARCH_LOCAL) != nullptr)
		return nullptr;//Prevent further searches

	return (searchScope != IStorage::SEARCH_DEFAULT || parent_ == nullptr) ? nullptr : parent_->findMemory(name, IStorage::SEARCH_DEFAULT);
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	FunctionMemory::ListType list;

	auto object = objects_.find(name);
	if (object != objects_.end() && dynamic_cast<IFunctionMemory *>(object->second.memory.get()) != nullptr)
		list.push_back(object->second);

	auto usedObject = usedObjects_.find(name);
	if (usedObject != usedObjects_.end() && dynamic_cast<IFunctionMemory *>(usedObject->second.get()) != nullptr)
		list.push_back({ usedObject->second, nullptr });

	for (auto item : usedStorages_){
		auto memory = item->findFunctionMemory(name, IStorage::SEARCH_LOCAL);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	if (searchScope == IStorage::SEARCH_DEFAULT && parent_ != nullptr){//Get all functions with same name
		auto memory = parent_->findFunctionMemory(name, IStorage::SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	return list.empty() ? nullptr : std::make_shared<FunctionMemory>(list);
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Storage::Storage::addOperatorMemory(const std::string &name){
	return &operators_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	FunctionMemory::ListType list;

	auto object = operators_.find(name);
	if (object != operators_.end())
		list.push_back(object->second);

	auto usedObject = usedOperators_.find(name);
	if (usedObject != usedOperators_.end())
		list.push_back({ usedObject->second, nullptr });

	for (auto item : usedStorages_){
		auto memory = item->findOperatorMemory(name, IStorage::SEARCH_LOCAL);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	if (searchScope == IStorage::SEARCH_DEFAULT && parent_ != nullptr){//Get all functions with same name
		auto memory = parent_->findOperatorMemory(name, IStorage::SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	return list.empty() ? nullptr : std::make_shared<FunctionMemory>(list);
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Storage::Storage::addTypenameOperatorMemory(IType::Ptr name){
	return &typeOperators_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::Storage::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	FunctionMemory::ListType list;
	for (auto &typeOperator : typeOperators_){
		if (typeOperator.first->isEqual(name))
			list.push_back(typeOperator.second);
	}

	for (auto &typeOperator : usedTypeOperators_){
		if (typeOperator.first->isEqual(name))
			list.push_back({ typeOperator.second, nullptr });
	}

	for (auto item : usedStorages_){
		auto memory = item->findTypenameOperatorMemory(name, IStorage::SEARCH_LOCAL);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	if (searchScope == IStorage::SEARCH_DEFAULT && parent_ != nullptr){//Get all functions with same name
		auto memory = parent_->findTypenameOperatorMemory(name, IStorage::SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	return list.empty() ? nullptr : std::make_shared<FunctionMemory>(list);
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
		if (object->second.memory == target){
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

bool StructuredScript::Storage::Storage::use(const std::string &name, IType::Ptr value){
	usedTypes_[name] = value;
	return true;
}

bool StructuredScript::Storage::Storage::use(const std::string &name, IMemory::Ptr value){
	usedObjects_[name] = value;
	return true;
}

bool StructuredScript::Storage::Storage::useOperator(const std::string &name, Memory::Ptr value){
	usedOperators_[name] = value;
	return true;
}

bool StructuredScript::Storage::Storage::useTypenameOperator(IType::Ptr name, IMemory::Ptr value){
	usedTypeOperators_[name] = value;
	return true;
}
