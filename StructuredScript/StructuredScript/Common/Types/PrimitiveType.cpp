#include "PrimitiveType.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::PrimitiveType::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::PrimitiveType::base(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::PrimitiveType::storage(){
	return nullptr;
}

bool StructuredScript::PrimitiveType::isAny(){
	return false;
}

bool StructuredScript::PrimitiveType::isEqual(Ptr target){
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

bool StructuredScript::PrimitiveType::isParent(Ptr target){
	return false;
}

bool StructuredScript::PrimitiveType::isCompatibleWith(Ptr target, bool family/* = false*/){
	if (isAny() || target->isAny())
		return true;

	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr){//Compare with declared type
		if (!isCompatibleWith(declaredType->value(), family))
			return false;

		auto states = StructuredScript::Storage::MemoryState(declaredType->states());
		return (!states.isConstant() && !states.isFinal());
	}

	auto compositeType = dynamic_cast<ICompositeType *>(target.get());
	if (compositeType != nullptr)//Compare with a list of different types
		return compositeType->isReversedCompatibleWith(ptr(), family);

	auto storage = dynamic_cast<IStorage *>(IGlobalStorage::globalStorage);
	auto numericType = storage->findType("numeric_type", true);
	if (target->isEqual(numericType))//Type is numeric -- Compatible: numeric & string types
		return (isEqual(numericType) || isEqual(storage->findType("string", true)));

	return (target.get() == this);
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::PrimitiveType::getCompatibleType(Ptr target, bool family /*= false*/){
	return isCompatibleWith(target, family) ? ptr() : nullptr;
}

std::string StructuredScript::PrimitiveType::name() const{
	return name_;
}

StructuredScript::Typename StructuredScript::PrimitiveType::value() const{
	return value_;
}

bool StructuredScript::AnyType::isAny(){
	return true;
}
