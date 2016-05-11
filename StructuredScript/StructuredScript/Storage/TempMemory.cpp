#include "TempMemory.h"

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::TempMemory::ptr(){
	return shared_from_this();
}

void StructuredScript::Storage::TempMemory::assign(IAny::Ptr object, IExceptionManager *exception, INode *expr){
	Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Invalid assignment!", expr)));
}

StructuredScript::IAny::Ptr StructuredScript::Storage::TempMemory::object(){
	return value_;
}

StructuredScript::DeclaredType *StructuredScript::Storage::TempMemory::type(){
	return nullptr;
}

StructuredScript::IMemoryAttributes *StructuredScript::Storage::TempMemory::attributes(){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Storage::TempMemory::storage(){
	return storage_;
}
