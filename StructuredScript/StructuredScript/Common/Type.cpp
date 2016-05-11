#include "Type.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::ptr(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::Type::storage(){
	return storage_;
}

bool StructuredScript::Type::isAny() const{
	return false;
}

bool StructuredScript::Type::isEqual(const IType &target) const{
	return (&target == this || isAny() || target.isAny());
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

std::shared_ptr<StructuredScript::IType> *StructuredScript::Type::addType(const std::string &name){
	return (findType(name, true) == nullptr) ? &types_[name] : nullptr;
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

StructuredScript::IMemory::Ptr *StructuredScript::Type::addMemory(const std::string &name){
	return (findMemory(name, true) == nullptr) ? &objects_[name] : nullptr;
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
			auto attribute = parent->findMemoryAttribute(name, false);
			if (attribute != nullptr)
				return attribute;
		}
	}

	return nullptr;
}

bool StructuredScript::Type::remove(const IMemory *target){
	return false;
}
