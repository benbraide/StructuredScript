#include "Memory.h"

StructuredScript::DeclaredType *StructuredScript::Storage::Memory::type(){
	return &type_;
}

StructuredScript::IMemoryAttributes *StructuredScript::Storage::Memory::attributes(){
	return &attributes_;
}
