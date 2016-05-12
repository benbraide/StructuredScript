#include "ObjectQuery.h"

bool StructuredScript::Query::Object::isPrimitive(IAny::Ptr object){
	return (dynamic_cast<IPrimitiveObject *>(object.get()) != nullptr);
}

bool StructuredScript::Query::Object::isUndefined(IAny::Ptr object){
	return (dynamic_cast<IUndefined *>(object.get()) != nullptr);
}
