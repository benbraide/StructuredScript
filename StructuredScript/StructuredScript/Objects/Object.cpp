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

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Objects::Object::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Objects::Object::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == type_->name())
		return this;

	if (searchScope != SEARCH_LOCAL){
		for (auto parent : parents_){
			auto storage = parent->findStorage(name, SEARCH_FAMILY);
			if (storage != nullptr)
				return storage;
		}
	}

	return (self_ == nullptr || self_ == this) ? nullptr : self_->findStorage(name, searchScope);
}

StructuredScript::IType::Ptr *StructuredScript::Objects::Object::addType(const std::string &name){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Object::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Object::addMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == "self"){
		auto memory = (self_ == nullptr) ? nullptr : self_->memory();
		return (memory == nullptr) ? nullptr : memory->ptr();
	}

	auto object = objects_.find(name);
	if (object != objects_.end())
		return object->second;

	auto storage = dynamic_cast<IStorage *>(type_.get());
	if (storage != nullptr){//Search immediate type content
		auto memory = storage->findMemory(name, SEARCH_LOCAL);
		if (memory != nullptr)
			return memory;
	}

	if (searchScope != SEARCH_LOCAL){
		for (auto parent : parents_){//Search parent objects and their immediate type contents
			auto object = parent->findMemory(name, SEARCH_FAMILY);
			if (object != nullptr)
				return object;
		}
	}

	if (self_ == nullptr || self_ == this){//Search storage using search scope
		storage = type_->storage();
		return (storage == nullptr) ? nullptr : storage->findMemory(name, searchScope);
	}

	return self_->findMemory(name, searchScope);//Forward search to object
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Object::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Object::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findTypenameOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
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
