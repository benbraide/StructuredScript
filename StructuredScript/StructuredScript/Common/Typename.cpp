#include "Typename.h"

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

bool StructuredScript::DeclaredType::isCompatibleWith(const DeclaredType &target) const{
	if (type_ == nullptr || target.type_ == nullptr || !type_->isCompatibleWith(*target.type_))
		return false;

	if (state_.isReference() && !target.state_.isReference())
		return false;

	if (target.state_.isFinal())
		return (state_.isFinal() || state_.isConstant());

	return (!target.state_.isConstant() || state_.isConstant());
}

bool StructuredScript::DeclaredType::isCompatibleWith(const IType *target) const{
	return (type_ != nullptr && target != nullptr && type_->isCompatibleWith(*target));
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

StructuredScript::DeclaredType::MemoryState &StructuredScript::DeclaredType::getState(){
	return state_;
}

StructuredScript::DeclaredType::MemoryAttribute &StructuredScript::DeclaredType::getAttribute(){
	return attribute_;
}
