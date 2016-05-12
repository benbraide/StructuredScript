#include "MemoryState.h"

StructuredScript::Storage::MemoryState &StructuredScript::Storage::MemoryState::operator =(unsigned short states){
	states_ = states;
	return *this;
}

StructuredScript::Storage::MemoryState &StructuredScript::Storage::MemoryState::operator +=(unsigned short states){
	states_ |= states;
	return *this;
}

StructuredScript::Storage::MemoryState &StructuredScript::Storage::MemoryState::operator-=(unsigned short states){
	states_ &= ~states;
	return *this;
}

unsigned short StructuredScript::Storage::MemoryState::states() const{
	return states_;
}

bool StructuredScript::Storage::MemoryState::is(unsigned short states, bool all /*= true*/) const{
	return all ? ((states_ & states) == states) : ((states_ & states) != 0u);
}

bool StructuredScript::Storage::MemoryState::isConstant() const{
	return ((states_ & STATE_CONSTANT) == STATE_CONSTANT);
}

bool StructuredScript::Storage::MemoryState::isFinal() const{
	return ((states_ & STATE_FINAL) == STATE_FINAL);
}

bool StructuredScript::Storage::MemoryState::isStatic() const{
	return ((states_ & STATE_STATIC) == STATE_STATIC);
}

bool StructuredScript::Storage::MemoryState::isPrivate() const{
	return ((states_ & STATE_PRIVATE) == STATE_PRIVATE);
}

bool StructuredScript::Storage::MemoryState::isProtected() const{
	return ((states_ & STATE_PROTECTED) == STATE_PROTECTED);
}

bool StructuredScript::Storage::MemoryState::isPublic() const{
	return ((states_ & (STATE_PRIVATE | STATE_PROTECTED)) == 0u);
}

bool StructuredScript::Storage::MemoryState::isReference() const{
	return ((states_ & STATE_REFERENCE) == STATE_REFERENCE);
}

bool StructuredScript::Storage::MemoryState::isRValReference() const{
	return ((states_ & STATE_RVALUE) == STATE_RVALUE);
}

bool StructuredScript::Storage::MemoryState::hasDefault() const{
	return ((states_ & (STATE_CONSTANT | STATE_FINAL | STATE_REFERENCE)) == 0u);
}

std::string StructuredScript::Storage::MemoryState::str() const{
	return "";
}
