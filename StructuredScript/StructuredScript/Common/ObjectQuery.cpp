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
	unsigned int value;

	if (getIndex<char, Objects::Primitive::CHAR_RANK>(object, value) || getIndex<unsigned char, Objects::Primitive::UCHAR_RANK>(object, value) ||
		getIndex<short, Objects::Primitive::SHORT_RANK>(object, value) || getIndex<unsigned short, Objects::Primitive::USHORT_RANK>(object, value) ||
		getIndex<int, Objects::Primitive::INT_RANK>(object, value) || getIndex<unsigned int, Objects::Primitive::UINT_RANK>(object, value) ||
		getIndex<long, Objects::Primitive::LONG_RANK>(object, value) || getIndex<unsigned long, Objects::Primitive::ULONG_RANK>(object, value) ||
		getIndex<long long, Objects::Primitive::LLONG_RANK>(object, value) || getIndex<unsigned long long, Objects::Primitive::ULLONG_RANK>(object, value)){
		return value;
	}

	return 0;
}

StructuredScript::IAny::Ptr StructuredScript::Query::Object::getObjectInStorage(IStorage *storage){
	while (storage != nullptr){
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		if (functionStorage != nullptr)
			return functionStorage->object();

		storage = storage->parent();
	}

	return nullptr;
}
