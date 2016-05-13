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
