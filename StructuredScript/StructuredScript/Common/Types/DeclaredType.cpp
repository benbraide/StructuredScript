#include "DeclaredType.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::DeclaredType::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::DeclaredType::base(){
	return value_->base();
}

StructuredScript::IStorage *StructuredScript::DeclaredType::storage(){
	return nullptr;
}

bool StructuredScript::DeclaredType::isAny(){
	return value_->isAny();
}

bool StructuredScript::DeclaredType::isEqual(Ptr target){
	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr){//Compare with declared type
		if (!isEqual_(declaredType->value()))
			return false;

		auto states = StructuredScript::Storage::MemoryState(declaredType->states());
		return (state_.isConstant() == states.isConstant() && state_.isFinal() == states.isFinal());
	}

	return (isEqual_(target) && (Query::Type::isComposite(target) || (!state_.isConstant() && !state_.isFinal())));
}

bool StructuredScript::DeclaredType::isParent(Ptr target){
	return value_->isParent(target);
}

bool StructuredScript::DeclaredType::isCompatibleWith(Ptr target, bool family/* = false*/){
	if (family || state_.isReference())//Types must be identical
		return (isEqual(target) || value_->isEqual(target) || value_->isParent(target));

	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr){//Compare with declared type
		if (!isCompatibleWith(declaredType->value(), family))
			return false;

		auto states = StructuredScript::Storage::MemoryState(declaredType->states());
		if (states.isFinal() && !state_.isConstant() && !state_.isFinal())//final type is compatible final & const types
			return false;

		return (!states.isConstant() || state_.isConstant());//const type is compatible with const types
	}

	auto compositeType = dynamic_cast<ICompositeType *>(target.get());
	if (compositeType != nullptr)//Compare with a list of different types
		return compositeType->isReversedCompatibleWith(ptr(), family);

	return value_->isCompatibleWith(target, family);
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::DeclaredType::getCompatibleType(Ptr target, bool family /*= false*/){
	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr){//Compare with declared type
		auto type = getCompatibleType(declaredType->value(), family || state_.isReference());
		if (type == nullptr)
			return nullptr;

		auto states = StructuredScript::Storage::MemoryState(declaredType->states());
		if (states.isFinal() && !state_.isConstant() && !state_.isFinal())//final type is compatible final & const types
			return nullptr;

		return (!states.isConstant() || state_.isConstant()) ? type : nullptr;//const type is compatible with const types
	}

	auto compositeType = dynamic_cast<ICompositeType *>(target.get());
	if (compositeType != nullptr)//Compare with a list of different types
		return compositeType->getReversedCompatibleType(ptr(), family || state_.isReference());

	return value_->getCompatibleType(target, family || state_.isReference());
}

std::string StructuredScript::DeclaredType::name() const{
	auto states = state_.str();
	return states.empty() ? value_->name() : (states + " " + value_->name());
}

StructuredScript::IType::Ptr StructuredScript::DeclaredType::value(){
	return value_;
}

unsigned short StructuredScript::DeclaredType::states() const{
	return state_.states();
}

void StructuredScript::DeclaredType::states(unsigned short value){
	state_ = value;
}

bool StructuredScript::DeclaredType::isEqual_(Ptr target){
	auto compositeType = dynamic_cast<ICompositeType *>(target.get());
	if (compositeType != nullptr)//Compare with a list of different types
		return compositeType->isReversedEqual(ptr());

	return value_->isEqual(target);
}
