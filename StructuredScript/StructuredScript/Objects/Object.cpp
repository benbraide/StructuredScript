#include "Object.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Object::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Object::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

bool StructuredScript::Objects::Object::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

std::string StructuredScript::Objects::Object::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "";
}

StructuredScript::IStorage *StructuredScript::Objects::Object::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == type_->name())
		return this;

	if (searchScope != SEARCH_LOCAL){
		for (auto parent : parents_){
			auto storage = dynamic_cast<IStorage *>(parent->object().get())->findStorage(name, SEARCH_FAMILY);
			if (storage != nullptr)
				return storage;
		}
	}

	if (self_ == nullptr || self_ == this)
		return (searchScope == SEARCH_DEFAULT) ? dynamic_cast<IStorage *>(type_.get())->findStorage(name) : nullptr;

	return self_->findStorage(name, searchScope);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;

	auto object = objects_.find(name);
	if (object != objects_.end()){
		if (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr)
			return object->second;

		list.push_back(object->second);
	}

	extendList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;

	auto object = objects_.find(name);
	if (object != objects_.end() && dynamic_cast<IFunctionMemory *>(object->second.get()) != nullptr)
		list.push_back(object->second);

	extendList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;
	extendOperatorList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;
	extendTypeOperatorList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::Object::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::Object::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

bool StructuredScript::Objects::Object::remove(IMemory::Ptr target){
	return false;
}

void StructuredScript::Objects::Object::self(Any *self){
	self_ = self;
}

void StructuredScript::Objects::Object::addParent(IMemory::Ptr parent){
	parents_.push_back(parent);
}

void StructuredScript::Objects::Object::extendList_(ListType &list, const std::string &name, unsigned short searchScope){
	if (self_ != nullptr && self_ != this){
		auto memory = self_->findFunctionMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back(memory);
	}

	if (searchScope != SEARCH_LOCAL){//Get all functions with same name
		auto memory = dynamic_cast<IStorage *>(type_.get())->findFunctionMemory(name, SEARCH_LOCAL);
		if (memory != nullptr)
			list.push_back(memory);

		for (auto parent : parents_){
			memory = dynamic_cast<IStorage *>(parent->object().get())->findFunctionMemory(name, SEARCH_FAMILY);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	if (searchScope == SEARCH_DEFAULT){//Get list from storage
		if (type_->storage() != nullptr){
			auto memory = type_->storage()->findFunctionMemory(name);
			if (memory != nullptr)
				list.push_back(memory);
		}
		else if (memory_->storage() != nullptr){
			auto memory = memory_->storage()->findFunctionMemory(name);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}
}

void StructuredScript::Objects::Object::extendOperatorList_(ListType &list, const std::string &name, unsigned short searchScope){
	if (self_ != nullptr && self_ != this){
		auto memory = self_->findOperatorMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back(memory);
	}

	if (searchScope != SEARCH_LOCAL){//Get all functions with same name
		auto memory = dynamic_cast<IStorage *>(type_.get())->findOperatorMemory(name, SEARCH_LOCAL);
		if (memory != nullptr)
			list.push_back(memory);

		for (auto parent : parents_){
			memory = dynamic_cast<IStorage *>(parent->object().get())->findOperatorMemory(name, SEARCH_FAMILY);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	if (searchScope == SEARCH_DEFAULT){//Get list from storage
		if (type_->storage() != nullptr){
			auto memory = type_->storage()->findOperatorMemory(name);
			if (memory != nullptr)
				list.push_back(memory);
		}
		else if (memory_->storage() != nullptr){
			auto memory = memory_->storage()->findOperatorMemory(name);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}
}

void StructuredScript::Objects::Object::extendTypeOperatorList_(ListType &list, IType::Ptr name, unsigned short searchScope){
	if (self_ != nullptr && self_ != this){
		auto memory = self_->findTypenameOperatorMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back(memory);
	}

	if (searchScope != SEARCH_LOCAL){//Get all functions with same name
		auto memory = dynamic_cast<IStorage *>(type_.get())->findTypenameOperatorMemory(name, SEARCH_LOCAL);
		if (memory != nullptr)
			list.push_back(memory);

		for (auto parent : parents_){
			memory = dynamic_cast<IStorage *>(parent->object().get())->findTypenameOperatorMemory(name, SEARCH_FAMILY);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	if (searchScope == SEARCH_DEFAULT){//Get list from storage
		if (type_->storage() != nullptr){
			auto memory = type_->storage()->findTypenameOperatorMemory(name);
			if (memory != nullptr)
				list.push_back(memory);
		}
		else if (memory_->storage() != nullptr){
			auto memory = memory_->storage()->findTypenameOperatorMemory(name);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}
}
