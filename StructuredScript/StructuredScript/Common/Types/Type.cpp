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
	auto nmspc = dynamic_cast<INamespace *>(storage_);
	return (nmspc == nullptr) ? name_ : (nmspc->name() + "::" + name_);
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
			auto type = dynamic_cast<Type *>(parent.get())->findType(name, SEARCH_FAMILY);
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
	ListType list;

	auto object = objects_.find(name);
	if (object != objects_.end()){
		if (dynamic_cast<IFunctionMemory *>(object->second.get()) == nullptr)
			return object->second;

		list.push_back(object->second);
	}

	if (list.empty()){//Search parents and storage
		if (searchScope == SEARCH_LOCAL)
			return nullptr;

		for (auto parent : parents_){
			auto object = dynamic_cast<Type *>(parent.get())->findMemory(name, SEARCH_FAMILY);
			if (object != nullptr)
				return object;
		}

		return (searchScope == SEARCH_DEFAULT && storage_ != nullptr) ? storage_->findMemory(name, SEARCH_DEFAULT) : nullptr;
	}

	extendList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;

	auto object = objects_.find(name);
	if (object != objects_.end() && dynamic_cast<IFunctionMemory *>(object->second.get()) != nullptr)
		list.push_back(object->second);

	extendList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addOperatorMemory(const std::string &name){
	return &operators_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;

	auto object = operators_.find(name);
	if (object != operators_.end())
		list.push_back(object->second);

	extendOperatorList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
}

StructuredScript::IMemory::Ptr *StructuredScript::Type::addTypenameOperatorMemory(IType::Ptr name){
	return &typeOperators_[name];
}

StructuredScript::IMemory::Ptr StructuredScript::Type::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;

	auto object = typeOperators_.find(name);
	if (object != typeOperators_.end())
		list.push_back(object->second);

	extendTypeOperatorList_(list, name, searchScope);
	return list.empty() ? nullptr : std::make_shared<StructuredScript::Storage::FunctionMemory>(list);
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

void StructuredScript::Type::addExternalCall(const std::string &name, ExternalCallType value){
	externalCalls_[name] = value;
}

StructuredScript::Type::TypenameOperatorMemoryListType::iterator StructuredScript::Type::findTypeOperator_(IType::Ptr name){
	for (auto item = typeOperators_.begin(); item != typeOperators_.end(); ++item){
		if (item->first->isEqual(name))
			return item;
	}

	return typeOperators_.end();
}

void StructuredScript::Type::extendList_(ListType &list, const std::string &name, unsigned short searchScope){
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
}

void StructuredScript::Type::extendOperatorList_(ListType &list, const std::string &name, unsigned short searchScope){
	if (searchScope != SEARCH_LOCAL){//Get all functions with same name
		for (auto parent : parents_){
			auto base = parent->base();
			auto storageParent = dynamic_cast<IStorage *>(base.get());

			auto memory = (storageParent == nullptr) ? nullptr : storageParent->findOperatorMemory(name, SEARCH_FAMILY);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	if (searchScope == SEARCH_DEFAULT && storage_ != nullptr){//Get list from storage
		auto memory = storage_->findOperatorMemory(name, SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back(memory);
	}
}

void StructuredScript::Type::extendTypeOperatorList_(ListType &list, IType::Ptr name, unsigned short searchScope){
	if (searchScope != SEARCH_LOCAL){//Get all functions with same name
		for (auto parent : parents_){
			auto base = parent->base();
			auto storageParent = dynamic_cast<IStorage *>(base.get());

			auto memory = (storageParent == nullptr) ? nullptr : storageParent->findTypenameOperatorMemory(name, SEARCH_FAMILY);
			if (memory != nullptr)
				list.push_back(memory);
		}
	}

	if (searchScope == SEARCH_DEFAULT && storage_ != nullptr){//Get list from storage
		auto memory = storage_->findTypenameOperatorMemory(name, SEARCH_DEFAULT);
		if (memory != nullptr)
			list.push_back(memory);
	}
}
