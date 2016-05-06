#include "CompositePrimitiveType.h"

bool StructuredScript::CompositePrimitiveType::isParent(const IType &target) const{
	return false;
}

std::string StructuredScript::CompositePrimitiveType::name() const{
	return name_;
}

StructuredScript::Typename StructuredScript::CompositePrimitiveType::value() const{
	return Typename::TYPE_NAME_NONE;
}

bool StructuredScript::CompositePrimitiveType::has(Typename value) const{
	for (auto type : types_){
		auto primitive = dynamic_cast<IPrimitiveType *>(type.get());
		if (primitive != nullptr && primitive->has(value))
			return true;
	}

	return false;
}

bool StructuredScript::CompositePrimitiveType::has(Typename from, Typename to) const{
	for (auto type : types_){
		auto primitive = dynamic_cast<IPrimitiveType *>(type.get());
		if (primitive != nullptr && primitive->has(from, to))
			return true;
	}

	return false;
}
