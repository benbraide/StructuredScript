#include "Type.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::base(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::Type::storage(){
	return storage_;
}

bool StructuredScript::Type::isAny(){
	return false;
}

bool StructuredScript::Type::isEqual(Ptr target){
	if (isAny() || target->isAny())
		return true;

	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr){//Compare with declared type
		if (!isEqual(declaredType->value()))
			return false;

		auto states = StructuredScript::Storage::MemoryState(declaredType->states());
		return (!states.isConstant() && !states.isFinal());
	}

	auto compositeType = dynamic_cast<ICompositeType *>(target.get());
	if (compositeType != nullptr)//Compare with a list of different types
		return compositeType->isReversedEqual(ptr());

	return (target.get() == this);
}

bool StructuredScript::Type::isParent(Ptr target){
	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr)//Use actual type
		target = declaredType->value();

	for (auto parent : parents_){
		if (parent->isEqual(target) || parent->isParent(target))
			return true;
	}

	return false;
}

bool StructuredScript::Type::isCompatibleWith(Ptr target, bool family/* = false*/){
	return (isEqual(target) || target->isParent(ptr()));
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::getCompatibleType(Ptr target, bool family /*= false*/){
	return isCompatibleWith(target, family) ? ptr() : nullptr;
}

std::string StructuredScript::Type::name() const{
	return name_;
}

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Type::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Type::findStorage(const std::string &name, bool localOnly){
	return dynamic_cast<IStorage *>(findType(name, localOnly).get());
}

std::shared_ptr<StructuredScript::IType> *StructuredScript::Type::addType(const std::string &name){
	return (findType(name, true) == nullptr) ? &types_[name] : nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Type::findType(const std::string &name, bool localOnly){
	auto type = types_.find(name);
	if (type != types_.end())
		return type->second;

	if (!localOnly){
		for (auto parent : parents_){
			auto alike = dynamic_cast<Type *>(parent.get());
			auto type = (alike == nullptr) ? nullptr : alike->findType(name, false);
			if (type != nullptr)
				return type;
		}
	}

	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addMemory(const std::string &name){
	auto object = objects_.find(name);
	if (object != objects_.end())//Check if it is a function memory
		return (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr) ? nullptr : &object->second;

	return &objects_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findMemory(const std::string &name, bool localOnly){
	auto object = objects_.find(name);
	if (object != objects_.end()){
		if (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr)
			return object->second;

		std::list<IMemory::Ptr> list({ object->second });
		if (!localOnly){//Get all functions with same name
			for (auto parent : parents_){
				auto base = parent->base();
				auto storageParent = dynamic_cast<IStorage *>(base.get());

				auto memory = (storageParent == nullptr) ? nullptr : storageParent->findFunctionMemory(name, false);
				if (memory != nullptr)
					list.push_back(memory);
			}
		}

		return std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
	}

	if (!localOnly){
		for (auto parent : parents_){
			auto alike = dynamic_cast<Type *>(parent.get());
			auto object = (alike == nullptr) ? nullptr : alike->findMemory(name, false);
			if (object != nullptr)
				return object;
		}
	}

	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findFunctionMemory(const std::string &name, bool localOnly){
	std::list<IMemory::Ptr> list;

	auto object = objects_.find(name);
	if (object != objects_.end() && dynamic_cast<IFunctionMemory *>(object->second.get()) != nullptr)
		list.push_back(object->second);

	if (!localOnly){//Get all functions with same name
		for (auto parent : parents_){
			auto base = parent->base();
			auto storageParent = dynamic_cast<IStorage *>(base.get());

			auto memory = (storageParent == nullptr) ? nullptr : storageParent->findFunctionMemory(name, false);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findOperatorMemory(const std::string &name, bool localOnly){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findTypenameOperatorMemory(const std::string &name, bool localOnly){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Type::addMemoryAttribute(const std::string &name){
	return (findMemoryAttribute(name, true) == nullptr) ? &attributes_[name] : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Type::findMemoryAttribute(const std::string &name, bool localOnly){
	auto attribute = attributes_.find(name);
	if (attribute != attributes_.end())
		return attribute->second;

	if (!localOnly){
		for (auto parent : parents_){
			auto alike = dynamic_cast<Type *>(parent.get());
			auto attribute = (alike == nullptr) ? nullptr : alike->findMemoryAttribute(name, false);
			if (attribute != nullptr)
				return attribute;
		}
	}

	return nullptr;
}

StructuredScript::IStorage::ExternalCallType StructuredScript::Type::findExternalCall(const std::string &name){
	return nullptr;
}

bool StructuredScript::Type::remove(IMemory::Ptr target){
	return false;
}
