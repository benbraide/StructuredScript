#include "TypeQuery.h"

bool StructuredScript::Query::Type::isAny(IType::Ptr type){
	return (dynamic_cast<IAnyType *>(type.get()) != nullptr);
}

bool StructuredScript::Query::Type::isComposite(IType::Ptr type){
	return (dynamic_cast<ICompositeType *>(type.get()) != nullptr);
}

bool StructuredScript::Query::Type::isStacked(IType::Ptr type){
	return (dynamic_cast<IStackedType *>(type.get()) != nullptr);
}

bool StructuredScript::Query::Type::isExpanded(IType::Ptr type){
	return (dynamic_cast<IExpandedType *>(type.get()) != nullptr);
}

bool StructuredScript::Query::Type::isArray(IType::Ptr type){
	return (dynamic_cast<IArrayType *>(type.get()) != nullptr);
}

bool StructuredScript::Query::Type::isConstant(IType::Ptr type){
	if (type == nullptr)
		return false;

	auto states = Storage::MemoryState(type->states());
	return states.isConstant();
}

bool StructuredScript::Query::Type::isFinal(IType::Ptr type){
	if (type == nullptr)
		return false;

	auto states = Storage::MemoryState(type->states());
	return states.isFinal();
}

bool StructuredScript::Query::Type::isMutable(IType::Ptr type){
	if (type == nullptr)
		return false;

	auto states = Storage::MemoryState(type->states());
	return (!states.isConstant() && !states.isFinal());
}

bool StructuredScript::Query::Type::isPrivate(IType::Ptr type){
	if (type == nullptr)
		return false;

	auto states = Storage::MemoryState(type->states());
	return states.isPrivate();
}

bool StructuredScript::Query::Type::isProtected(IType::Ptr type){
	if (type == nullptr)
		return false;

	auto states = Storage::MemoryState(type->states());
	return states.isProtected();
}

bool StructuredScript::Query::Type::isStatic(IType::Ptr type){
	if (type == nullptr)
		return false;

	auto states = Storage::MemoryState(type->states());
	return states.isStatic();
}
