#include "CompositePrimitiveType.h"

bool StructuredScript::CompositePrimitiveType::isParent(Ptr target){
	return false;
}

std::string StructuredScript::CompositePrimitiveType::name() const{
	return name_;
}

StructuredScript::Typename StructuredScript::CompositePrimitiveType::value() const{
	return Typename::TYPE_NAME_NONE;
}
