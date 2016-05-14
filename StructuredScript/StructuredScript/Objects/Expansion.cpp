#include "Expansion.h"

void StructuredScript::Objects::Expansion::expand(IFunction::ArgListType &args){
	for (auto entry : entries_)
		args.push_back(entry->object());
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::add(){
	if (memory_ == nullptr)
		return *entries_.emplace(entries_.end(), std::make_shared<Storage::Memory>(nullptr, type_, nullptr, nullptr));
	return *entries_.emplace(entries_.end(), std::make_shared<Storage::Memory>(memory_->storage(), type_, nullptr, memory_->attributes()));
}
