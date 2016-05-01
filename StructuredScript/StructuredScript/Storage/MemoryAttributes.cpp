#include "MemoryAttributes.h"

StructuredScript::Storage::MemoryAttribute &StructuredScript::Storage::MemoryAttribute::operator =(unsigned short attributes){
	attributes_ = attributes;
	return *this;
}

StructuredScript::Storage::MemoryAttribute &StructuredScript::Storage::MemoryAttribute::operator +=(unsigned short attributes){
	attributes_ |= attributes;
	return *this;
}

StructuredScript::Storage::MemoryAttribute &StructuredScript::Storage::MemoryAttribute::operator-=(unsigned short attributes){
	attributes_ &= ~attributes;
	return *this;
}

unsigned short StructuredScript::Storage::MemoryAttribute::getAttributes() const{
	return attributes_;
}

bool StructuredScript::Storage::MemoryAttribute::is(unsigned short attributes, bool all /*= true*/) const{
	return all ? ((attributes_ & attributes) == attributes) : ((attributes_ & attributes) != 0u);
}

bool StructuredScript::Storage::MemoryAttribute::isLocked() const{
	return ((attributes_ & ATTRIBUTE_LOCKED) == ATTRIBUTE_LOCKED);
}

bool StructuredScript::Storage::MemoryAttribute::isConcurrent() const{
	return ((attributes_ & ATTRIBUTE_CONCURRENT) == ATTRIBUTE_CONCURRENT);
}
