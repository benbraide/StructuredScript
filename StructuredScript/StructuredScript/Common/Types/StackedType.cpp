#include "StackedType.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::StackedType::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::StackedType::base(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::StackedType::storage(){
	return nullptr;
}

bool StructuredScript::StackedType::isAny(){
	return false;
}

bool StructuredScript::StackedType::isParent(Ptr target){
	return false;
}

bool StructuredScript::StackedType::isCompatibleWith(Ptr target, bool family /*= false*/){
	return isEqual(target);
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::StackedType::getCompatibleType(Ptr target, bool family /*= false*/){
	return isEqual(target) ? shared_from_this() : nullptr;
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::StackedType::value(){
	return value_;
}

unsigned short StructuredScript::StackedType::states() const {
	return 0;
}

bool StructuredScript::ExpandedType::isEqual(Ptr target){
	return Query::Type::isExpanded(target);
}

std::string StructuredScript::ExpandedType::name() const{
	return (value_->name() + "...");
}
