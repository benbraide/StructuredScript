#include "TempMemory.h"

StructuredScript::Storage::TempMemory::TempMemory(IStorage *storage, IAny::Ptr value) 
	: storage_(storage), value_(value){
	value_->setMemory(this);
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::TempMemory::ptr(){
	return shared_from_this();
}

void StructuredScript::Storage::TempMemory::assign(IAny::Ptr object, IExceptionManager *exception, INode *expr){
	if (value_ != nullptr)//Unbind previous
		value_->setMemory(nullptr);

	value_ = object;
	value_->setMemory(this);
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
