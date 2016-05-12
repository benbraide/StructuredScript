#include "Any.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Any::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Any::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Any::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

StructuredScript::IAny *StructuredScript::Objects::Any::base(){
	return this;
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
	return false;
}

std::string StructuredScript::Objects::Any::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "";
}

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Objects::Any::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Objects::Any::findStorage(const std::string &name, bool localOnly){
	if (name == type_->name())
		return this;

	if (!localOnly){
		for (auto parent : parents_){
			auto storage = parent->findStorage(name, false);
			if (storage != nullptr)
				return storage;
		}
	}

	return (self_ == nullptr || self_ == this) ? nullptr : self_->findStorage(name, localOnly);
}

StructuredScript::IType::Ptr *StructuredScript::Objects::Any::addType(const std::string &name){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Any::findType(const std::string &name, bool localOnly){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Any::addMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findMemory(const std::string &name, bool localOnly){
	if (name == "self"){
		auto memory = (self_ == nullptr) ? nullptr : self_->memory();
		return (memory == nullptr) ? nullptr : memory->ptr();
	}

	auto object = objects_.find(name);
	if (object != objects_.end())
		return object->second;

	if (!localOnly){
		for (auto parent : parents_){
			auto object = parent->findMemory(name, false);
			if (object != nullptr)
				return object;
		}
	}

	return (self_ == nullptr || self_ == this) ? nullptr : self_->findMemory(name, localOnly);
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Any::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findOperatorMemory(const std::string &name, bool localOnly){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Any::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findTypenameOperatorMemory(const std::string &name, bool localOnly){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::Any::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::Any::findMemoryAttribute(const std::string &name, bool localOnly){
	return nullptr;
}

bool StructuredScript::Objects::Any::remove(IMemory::Ptr target){
	return false;
}
