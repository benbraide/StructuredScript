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

	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Any::addMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Any::findMemory(const std::string &name, bool localOnly){
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

	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Any::findType(const std::string &name, bool localOnly){
	return nullptr;
}

bool StructuredScript::Objects::Any::remove(const IMemory *target){
	return false;
}
