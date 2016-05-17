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

	auto index = Query::Object::getIndex(right);
	if (index >= entries_.size()){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Index is out of bounds!", expr)));
	}

	return entries_[index]->object();
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

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Expansion::addMemory(const std::string &name){
	return (name == "length" && length_ == nullptr) ? &length_ : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return (name == "length") ? length_ : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Expansion::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::Expansion::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::findTypenameOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::Expansion::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::Expansion::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::Objects::Expansion::ExternalCallType StructuredScript::Objects::Expansion::findExternalCall(const std::string &name){
	return (name == "length.get") ? lengthCallback_ : nullptr;
}

bool StructuredScript::Objects::Expansion::remove(IMemory::Ptr target){
	return nullptr;
}

void StructuredScript::Objects::Expansion::expand(IFunction::ArgListType &args){
	for (auto entry : entries_)
		args.push_back(entry->object());
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Expansion::add(){
	if (memory_ == nullptr)
		return *entries_.emplace(entries_.end(), std::make_shared<StructuredScript::Storage::Memory>(nullptr, type_, nullptr, nullptr));
	return *entries_.emplace(entries_.end(), std::make_shared<StructuredScript::Storage::Memory>(memory_->storage(), type_, nullptr, memory_->attributes()));
}

void StructuredScript::Objects::Expansion::init(){
	Parser::Parser parser;
	Scanner::Scanner scanner;
	Scanner::StringCharacterWell well("any length{ @[Call(length.get)]unsigned int get() }");

	lengthNode_ = parser.parse(well, scanner, nullptr);

	lengthCallback_ = [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto exspansion = dynamic_cast<Expansion *>(storageBase.get());
		if (exspansion == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createUInt(exspansion->entries_.size());
	};
}

StructuredScript::INode::Ptr StructuredScript::Objects::Expansion::lengthNode_;

StructuredScript::Objects::Expansion::ExternalCallType StructuredScript::Objects::Expansion::lengthCallback_;