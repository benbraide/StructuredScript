#include "TypeQuery.h"

bool StructuredScript::Query::Type::isAny(const IType *type){
	return (dynamic_cast<const IAnyType *>(type) != nullptr);
}
