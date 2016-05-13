#include "MemoryAttributes.h"

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Storage::MemoryAttributes::ptr(){
	return shared_from_this();
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::MemoryAttributes::getAttribute(const std::string &name){
	auto attribute = attributes_.find(name);
	return (attribute == attributes_.end()) ? nullptr : attribute->second;
}

bool StructuredScript::Storage::MemoryAttributes::hasAttribute(const std::string &name) const{
	return (attributes_.find(name) != attributes_.end());
}

std::string StructuredScript::Storage::MemoryAttributes::str() const{
	return "";
}
