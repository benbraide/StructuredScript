#include "DeclaredType.h"

bool StructuredScript::DeclaredType::operator ==(const DeclaredType &right) const{
	return isEqual(right, false);
}

bool StructuredScript::DeclaredType::operator ==(const IType *right) const{
	return isEqual(right, false);
}

bool StructuredScript::DeclaredType::operator !=(const DeclaredType &right) const{
	return !isEqual(right, false);
}

bool StructuredScript::DeclaredType::operator !=(const IType *right) const{
	return !isEqual(right, false);
}

bool StructuredScript::DeclaredType::isCompatibleWith(const DeclaredType &target, bool family /*= false*/) const{
	return isCompatibleWith(type_, state_, family);
}

bool StructuredScript::DeclaredType::isCompatibleWith(const IType *type, const MemoryState &state, bool family /*= false*/) const{
	if (type_ == nullptr || type == nullptr)
		return false;

	if (state_.isReference()){//Types must be identical
		if (!state.isReference() || (!type_->isEqual(*type) && !type->isParent(*type_)))
			return false;
	}
	else if (family && !type_->isEqual(*type) && !type->isParent(*type_))
		return false;
	else if (!family && !type_->isCompatibleWith(*type))
		return false;

	if (state.isFinal())
		return (state_.isFinal() || state_.isConstant());

	return (!state.isConstant() || state_.isConstant());
}

bool StructuredScript::DeclaredType::isEqual(const DeclaredType &target, bool strictly /*= true*/) const{
	if (type_ == nullptr || target.type_ == nullptr)
		return false;

	if (!strictly)
		return (type_ == target.type_);

	return (state_.isFinal() == target.state_.isFinal() && state_.isConstant() == target.state_.isConstant() &&
		state_.isReference() == target.state_.isReference() && state_.isRValReference() == target.state_.isRValReference());
}

bool StructuredScript::DeclaredType::isEqual(const IType *target, bool strictly /*= true*/) const{
	if (type_ == nullptr || target == nullptr)
		return false;

	if (!strictly)
		return (type_ == target);

	return (!state_.isFinal() && !state_.isConstant() && !state_.isReference() && !state_.isRValReference());
}

StructuredScript::IType *StructuredScript::DeclaredType::type(){
	return type_;
}

StructuredScript::DeclaredType::MemoryState &StructuredScript::DeclaredType::state(){
	return state_;
}
