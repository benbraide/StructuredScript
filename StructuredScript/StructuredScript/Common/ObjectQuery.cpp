#include "ObjectQuery.h"
#include "../Objects/TypedPrimitive.h"

bool StructuredScript::Query::Object::isPrimitive(IAny::Ptr object){
	auto objectBase = (object == nullptr) ? nullptr : object->base();
	return (dynamic_cast<IPrimitiveObject *>(objectBase.get()) != nullptr);
}

bool StructuredScript::Query::Object::isUndefined(IAny::Ptr object){
	auto objectBase = (object == nullptr) ? nullptr : object->base();
	return (dynamic_cast<IUndefined *>(objectBase.get()) != nullptr);
}

bool StructuredScript::Query::Object::isExpansion(IAny::Ptr object){
	auto objectBase = (object == nullptr) ? nullptr : object->base();
	return (dynamic_cast<IExpansion *>(objectBase.get()) != nullptr);
}

bool StructuredScript::Query::Object::isExpanded(IAny::Ptr object){
	auto objectBase = (object == nullptr) ? nullptr : object->base();
	return (dynamic_cast<IExpanded *>(objectBase.get()) != nullptr);
}

unsigned int StructuredScript::Query::Object::getIndex(IAny::Ptr object){
	return getIndexValue<unsigned int>(object);
}

StructuredScript::IAny *StructuredScript::Query::Object::getObjectInStorage(IStorage *storage){
	while (storage != nullptr){
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		if (functionStorage != nullptr)
			return functionStorage->object();

		storage = storage->parent();
	}

	return nullptr;
}
