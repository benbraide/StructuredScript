#include "PrimitiveType.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::PrimitiveType::ptr(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::PrimitiveType::storage(){
	return nullptr;
}

bool StructuredScript::PrimitiveType::isAny() const{
	return false;
}

bool StructuredScript::PrimitiveType::isEqual(const IType &target) const{
	if (&target == this || has(Typename::TYPE_NAME_ANY))
		return true;

	auto primitive = dynamic_cast<const IPrimitiveType *>(&target);
	return (primitive != nullptr && (primitive->has(Typename::TYPE_NAME_ANY) || primitive->has(value_)));
}

bool StructuredScript::PrimitiveType::isParent(const IType &target) const{
	return false;
}

bool StructuredScript::PrimitiveType::isCompatibleWith(const IType &target) const{
	if (&target == this || has(Typename::TYPE_NAME_ANY))
		return true;

	auto primitive = dynamic_cast<const IPrimitiveType *>(&target);
	if (primitive == nullptr)
		return false;

	if (primitive->has(Typename::TYPE_NAME_ANY) || primitive->has(value_))
		return true;

	if (primitive->has(Typename::TYPE_NAME_NAN, Typename::TYPE_NAME_LDOUBLE))//Numeric types
		return has(Typename::TYPE_NAME_NAN, Typename::TYPE_NAME_STRING);

	return false;
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::PrimitiveType::getCompatibleType(const IType &target){
	return isCompatibleWith(target) ? ptr() : nullptr;
}

std::string StructuredScript::PrimitiveType::name() const{
	return name_;
}

StructuredScript::Typename StructuredScript::PrimitiveType::value() const{
	return value_;
}

bool StructuredScript::PrimitiveType::has(Typename value) const{
	return (value_ == value);
}

bool StructuredScript::PrimitiveType::has(Typename from, Typename to) const{
	return (value_ >= from && value_ <= to);
}

bool StructuredScript::AnyType::isAny() const{
	return true;
}
