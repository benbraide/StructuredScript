#include "CompositeType.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::CompositeType::ptr(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::CompositeType::storage(){
	return nullptr;
}

bool StructuredScript::CompositeType::isEqual(const IType &target) const{
	for (auto type : types_){
		if (type->isEqual(target))
			return true;
	}

	return false;
}

bool StructuredScript::CompositeType::isParent(const IType &target) const{
	for (auto type : types_){
		if (type->isParent(target))
			return true;
	}

	return false;
}

bool StructuredScript::CompositeType::isCompatibleWith(const IType &target) const{
	for (auto type : types_){
		if (type->isEqual(target) || target.isParent(*type))
			return true;
	}

	return false;
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::CompositeType::getCompatibleType(const IType &target){
	for (auto type : types_){
		if (type->isEqual(target) || target.isParent(*type))
			return type;
	}

	return nullptr;
}

std::string StructuredScript::CompositeType::name() const{
	std::string value;
	for (auto type : types_){
		if (value.empty())
			value = type->name();
		else
			value += ", " + type->name();
	}

	return ("any<" + value + ">");
}
