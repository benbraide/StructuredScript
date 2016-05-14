#include "CompositeType.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::CompositeType::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::CompositeType::base(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::CompositeType::storage(){
	return nullptr;
}

bool StructuredScript::CompositeType::isAny(){
	for (auto type : types_){
		if (type->isAny())
			return true;
	}

	return types_.empty();
}

bool StructuredScript::CompositeType::isEqual(Ptr target){
	for (auto type : types_){
		if (type->isEqual(target))
			return true;
	}

	return false;
}

bool StructuredScript::CompositeType::isParent(Ptr target){
	for (auto type : types_){
		if (type->isParent(target))
			return true;
	}

	return false;
}

bool StructuredScript::CompositeType::isCompatibleWith(Ptr target, bool family/* = false*/){
	for (auto type : types_){
		if (type->isEqual(target) || target->isParent(type))
			return true;
	}

	return false;
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::CompositeType::getCompatibleType(Ptr target, bool family/* = false*/){
	IType::Ptr match;
	for (auto type : types_){
		if (type->isEqual(target))
			return type;

		if (target->isParent(type)){//Get nearest parent
			if (match == nullptr || type->isParent(match))
				match = type;
		}
	}

	return match;
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

bool StructuredScript::CompositeType::isReversedEqual(IType::Ptr target){
	for (auto type : types_){
		if (target->isEqual(type))
			return true;
	}

	return false;
}

bool StructuredScript::CompositeType::isReversedParent(IType::Ptr target){
	for (auto type : types_){
		if (target->isParent(type))
			return true;
	}

	return false;
}

bool StructuredScript::CompositeType::isReversedCompatibleWith(IType::Ptr target, bool family /*= false*/){
	for (auto type : types_){
		if (target->isCompatibleWith(type, family))
			return true;
	}

	return false;
}

StructuredScript::IType::Ptr StructuredScript::CompositeType::getReversedCompatibleType(IType::Ptr target, bool family /*= false*/){
	for (auto type : types_){
		if (target->isCompatibleWith(type, family))
			return type;
	}

	return nullptr;
}
