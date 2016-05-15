#include "Type.h"

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::base(){
	return shared_from_this();
}

StructuredScript::IStorage *StructuredScript::Type::storage(){
	return storage_;
}

bool StructuredScript::Type::isAny(){
	return false;
}

bool StructuredScript::Type::isEqual(Ptr target){
	if (isAny() || target->isAny())
		return true;

	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr){//Compare with declared type
		if (!isEqual(declaredType->value()))
			return false;

		auto states = StructuredScript::Storage::MemoryState(declaredType->states());
		return (!states.isConstant() && !states.isFinal());
	}

	auto compositeType = dynamic_cast<ICompositeType *>(target.get());
	if (compositeType != nullptr)//Compare with a list of different types
		return compositeType->isReversedEqual(ptr());

	return (target.get() == this);
}

bool StructuredScript::Type::isParent(Ptr target){
	auto declaredType = dynamic_cast<IDeclaredType *>(target.get());
	if (declaredType != nullptr)//Use actual type
		target = declaredType->value();

	for (auto parent : parents_){
		if (parent->isEqual(target) || parent->isParent(target))
			return true;
	}

	return false;
}

bool StructuredScript::Type::isCompatibleWith(Ptr target, bool family/* = false*/){
	return (isEqual(target) || target->isParent(ptr()));
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::Type::getCompatibleType(Ptr target, bool family /*= false*/){
	return isCompatibleWith(target, family) ? ptr() : nullptr;
}

std::string StructuredScript::Type::name() const{
	return name_;
}

unsigned short StructuredScript::Type::states() const {
	return 0;
}

StructuredScript::IStorage *StructuredScript::Type::parent(){
	return storage_;
}

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Type::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Type::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return dynamic_cast<IStorage *>(findType(name, searchScope).get());
}

std::shared_ptr<StructuredScript::IType> *StructuredScript::Type::addType(const std::string &name){
	return (findType(name, true) == nullptr) ? &types_[name] : nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Type::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto type = types_.find(name);
	if (type != types_.end())
		return type->second;

	if (searchScope != SEARCH_LOCAL){
		for (auto parent : parents_){
			auto alike = dynamic_cast<Type *>(parent.get());
			auto type = (alike == nullptr) ? nullptr : alike->findType(name, SEARCH_FAMILY);
			if (type != nullptr)
				return type;
		}
	}

	return (searchScope == SEARCH_DEFAULT && storage_ != nullptr) ? storage_->findType(name, SEARCH_DEFAULT) : nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addMemory(const std::string &name){
	auto object = objects_.find(name);
	if (object != objects_.end())//Check if it is a function memory
		return (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr) ? nullptr : &object->second;

	return &objects_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto memory = findMemberMemory(name, searchScope);
	if (memory == nullptr)
		return nullptr;

	auto functionMemory = dynamic_cast<StructuredScript::Storage::FunctionMemory *>(memory.get());
	if (functionMemory != nullptr){//Get static memories
		StructuredScript::Storage::FunctionMemory::ListType list;

		functionMemory->getStaticMemories(list);
		if (list.empty())//No static memories found
			return nullptr;

		if (list.size() == functionMemory->count())//All entries were static
			return memory;

		return std::make_shared<StructuredScript::Storage::FunctionMemory>(list);//Create new function with sub list
	}

	auto type = memory->type();
	auto declaredType = dynamic_cast<IDeclaredType *>(type.get());

	auto states = (declaredType == nullptr) ? StructuredScript::Storage::MemoryState::STATE_NONE : declaredType->states();
	auto state = StructuredScript::Storage::MemoryState(states);

	return state.isStatic() ? memory : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	StructuredScript::Storage::FunctionMemory::ListType list;

	auto object = objects_.find(name);
	auto functionMemory = (object == objects_.end()) ? nullptr : dynamic_cast<StructuredScript::Storage::FunctionMemory *>(object->second.get());

	if (functionMemory != nullptr)
		functionMemory->getStaticMemories(list);

	if (searchScope != SEARCH_LOCAL){//Get all functions with same name
		for (auto parent : parents_){
			auto base = parent->base();
			auto storageParent = dynamic_cast<IStorage *>(base.get());

			auto memory = (storageParent == nullptr) ? nullptr : storageParent->findFunctionMemory(name, SEARCH_FAMILY);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	if (searchScope == SEARCH_DEFAULT && storage_ != nullptr){//Get list from storage
		auto memory = storage_->findFunctionMemory(name, SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back(memory);
	}

	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findTypenameOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Type::addMemoryAttribute(const std::string &name){
	return (findMemoryAttribute(name, true) == nullptr) ? &attributes_[name] : nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Type::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto attribute = attributes_.find(name);
	if (attribute != attributes_.end())
		return attribute->second;

	if (searchScope != SEARCH_LOCAL){
		for (auto parent : parents_){
			auto alike = dynamic_cast<Type *>(parent.get());
			auto attribute = (alike == nullptr) ? nullptr : alike->findMemoryAttribute(name, SEARCH_FAMILY);
			if (attribute != nullptr)
				return attribute;
		}
	}

	return (searchScope == SEARCH_DEFAULT && storage_ != nullptr) ? storage_->findMemoryAttribute(name, SEARCH_DEFAULT) : nullptr;
}

StructuredScript::IStorage::ExternalCallType StructuredScript::Type::findExternalCall(const std::string &name){
	auto call = externalCalls_.find(name);
	return (call == externalCalls_.end()) ? nullptr : call->second;
}

bool StructuredScript::Type::remove(IMemory::Ptr target){
	return false;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findMemberMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto object = objects_.find(name);
	if (object != objects_.end()){
		if (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr)
			return object->second;

		std::list<IMemory::Ptr> list({ object->second });
		if (searchScope != SEARCH_LOCAL){//Get all functions with same name
			for (auto parent : parents_){
				auto base = parent->base();
				auto storageParent = dynamic_cast<IStorage *>(base.get());

				auto memory = (storageParent == nullptr) ? nullptr : storageParent->findFunctionMemory(name, SEARCH_FAMILY);
				if (memory != nullptr)
					list.push_back(memory);
			}
		}

		if (searchScope == SEARCH_DEFAULT && storage_ != nullptr){//Get list from storage
			auto memory = storage_->findFunctionMemory(name, SEARCH_DEFAULT);
			if (memory != nullptr)
				list.push_back(memory);
		}

		return std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
	}

	if (searchScope != SEARCH_LOCAL){
		for (auto parent : parents_){
			auto alike = dynamic_cast<Type *>(parent.get());
			auto object = (alike == nullptr) ? nullptr : alike->findMemory(name, searchScope);
			if (object != nullptr)
				return object;
		}
	}

	return (searchScope == SEARCH_DEFAULT && storage_ != nullptr) ? storage_->findMemory(name, SEARCH_DEFAULT) : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findMemberFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	std::list<IMemory::Ptr> list;

	auto object = objects_.find(name);
	if (object != objects_.end() && dynamic_cast<IFunctionMemory *>(object->second.get()) != nullptr)
		list.push_back(object->second);

	if (searchScope != SEARCH_LOCAL){//Get all functions with same name
		for (auto parent : parents_){
			IMemory::Ptr memory;

			auto base = parent->base();
			auto compoundType = dynamic_cast<ICompoundType *>(base.get());

			if (compoundType == nullptr){
				auto storageType = dynamic_cast<IStorage *>(base.get());
				memory = (storageType == nullptr) ? nullptr : storageType->findFunctionMemory(name, SEARCH_FAMILY);
			}
			else
				memory = compoundType->findMemberFunctionMemory(name, SEARCH_FAMILY);

			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	if (searchScope == SEARCH_DEFAULT && storage_ != nullptr){//Get list from storage
		auto memory = storage_->findFunctionMemory(name, SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back(memory);
	}

	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findMemberOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findMemberTypenameOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

void StructuredScript::Type::addExternalCall(const std::string &name, ExternalCallType value){
	externalCalls_[name] = value;
}
