#include "Expansion.h"

StructuredScript::Objects::Expansion::Expansion(IType::Ptr type)
	: Primitive(type){
	lengthNode_->evaluate(this, nullptr, nullptr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Expansion::assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot assign to an expansion object!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Expansion::evaluateBinary(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	if (value != "[]")
		return Primitive::evaluateBinary(value, right, storage, exception, expr);

	auto rightBase = right->base();
	if (dynamic_cast<IInteger *>(rightBase.get()) == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'[]': Expected index to be an integral value!", expr)));
	}

	auto index = Query::Object::getIndex(rightBase);
	if (index >= entries_.size()){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Index is out of bounds!", expr)));
	}

	return entries_[index].value;
}

StructuredScript::IStorage *StructuredScript::Objects::Expansion::parent(){
	return nullptr;
}

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Objects::Expansion::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Objects::Expansion::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return dynamic_cast<IStorage *>(IGlobalStorage::globalStorage)->findStorage(name, searchScope);
}

StructuredScript::IType::Ptr *StructuredScript::Objects::Expansion::addType(const std::string &name){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Expansion::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return dynamic_cast<IStorage *>(IGlobalStorage::globalStorage)->findType(name, searchScope);
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Objects::Expansion::addMemory(const std::string &name){
	return (name == "length" && length_.memory == nullptr) ? &length_ : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return (name == "length") ? length_.memory : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Objects::Expansion::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Objects::Expansion::addTypenameOperatorMemory(IType::Ptr name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::Expansion::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::Expansion::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::Objects::Expansion::ExternalCallType StructuredScript::Objects::Expansion::findExternalCall(const std::string &name){
	return (name == "0") ? lengthCallback_ : nullptr;
}

bool StructuredScript::Objects::Expansion::remove(IMemory::Ptr target){
	return nullptr;
}

void StructuredScript::Objects::Expansion::expand(IFunction::ArgListType &args){
	for (auto entry : entries_)
		args.push_back(entry.value);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::add(){
	auto storage = (memory_ == nullptr) ? nullptr : memory_->storage();
	auto attributes = (memory_ == nullptr) ? nullptr : memory_->attributes();

	auto info = entries_.emplace(entries_.end(), IStorage::MemoryInfo{ nullptr, nullptr });
	auto memory = std::make_shared<StructuredScript::Storage::Memory>(&*info, storage, type_, attributes);

	return (info->memory = memory);
}

void StructuredScript::Objects::Expansion::init(){
	lengthNode_ = IGlobalStorage::globalStorage->parse("any length{ @[Call(0)]unsigned int get() }");

	lengthCallback_ = [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto exspansion = (functionStorage == nullptr) ? nullptr : dynamic_cast<Expansion *>(functionStorage->object()->memory()->storage());
		if (exspansion == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createUInt(exspansion->entries_.size());
	};
}

StructuredScript::INode::Ptr StructuredScript::Objects::Expansion::lengthNode_;

StructuredScript::Objects::Expansion::ExternalCallType StructuredScript::Objects::Expansion::lengthCallback_;