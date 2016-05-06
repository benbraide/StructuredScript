#include "Type.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::ptr(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::Type::storage(){
	return storage_;
}

bool StructuredScript::Type::isEqual(const IType &target) const{
	return (&target == this || Query<IType>::isAnyType(this) || Query<IType>::isAnyType(&target));
}

bool StructuredScript::Type::isParent(const IType &target) const{
	for (auto parent : parents_){
		if (parent == &target || parent->isParent(target))
			return true;
	}

	return false;
}

bool StructuredScript::Type::isCompatibleWith(const IType &target) const{
	return false;
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::getCompatibleType(const IType &target){
	return nullptr;
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

StructuredScript::IMemory::Ptr *StructuredScript::Type::addMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findMemory(const std::string &name, bool localOnly){
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

StructuredScript::IType::Ptr StructuredScript::Type::findType(const std::string &name, bool localOnly){
	auto type = types_.find(name);
	if (type != types_.end())
		return type->second;

	if (!localOnly){
		for (auto parent : parents_){
			auto type = parent->findType(name, false);
			if (type != nullptr)
				return type;
		}
	}

	return nullptr;
}

bool StructuredScript::Type::remove(const IMemory *target){
	return false;
}
