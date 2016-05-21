#include "IdentifierNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IdentifierNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IdentifierNode::clone(){
	return std::make_shared<IdentifierNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::IdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (storage == nullptr)
		return nullptr;

	auto memory = storage->findMemory(value_);
	if (memory == nullptr){
		auto type = storage->findType(value_);
		if (type == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve identifier!", expr)));
		}

		return PrimitiveFactory::createTypeObject(type);
	}

	if (dynamic_cast<IFunctionMemory *>(memory.get()) == nullptr)
		return memory->object();

	return PrimitiveFactory::createFunctionObject(memory);
}

std::string StructuredScript::Nodes::IdentifierNode::str(){
	return value_;
}

void StructuredScript::Nodes::IdentifierNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::IdentifierNode::attributes(){
	return nullptr;
}

std::string StructuredScript::Nodes::IdentifierNode::value() const{
	return value_;
}

StructuredScript::IStorage *StructuredScript::Nodes::IdentifierNode::resolveStorage(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	return (storage == nullptr) ? nullptr : storage->findStorage(value_, searchScope);
}

StructuredScript::IType::Ptr StructuredScript::Nodes::IdentifierNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	return (storage == nullptr) ? nullptr : storage->findType(value_, searchScope);
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::IdentifierNode::resolveMemory(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	return (storage == nullptr) ? nullptr : storage->findMemory(value_, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Nodes::IdentifierNode::addMemory(IStorage *storage){
	return storage->addMemory(value_);
}

StructuredScript::IMemory::Ptr *StructuredScript::Nodes::IdentifierNode::addNonOperatorMemory(IStorage *storage){
	return storage->addMemory(value_);
}

bool StructuredScript::Nodes::IdentifierNode::use(IPureStorage *target, IStorage *storage){
	auto memory = resolveMemory(storage);
	if (memory == nullptr){
		auto type = storage->findType(value_);
		return (type == nullptr) ? false : target->use(value_, type);
	}

	return target->use(value_, memory);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::OperatorIdentifierNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::OperatorIdentifierNode::clone(){
	return std::make_shared<OperatorIdentifierNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::OperatorIdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return nullptr;
}

std::string StructuredScript::Nodes::OperatorIdentifierNode::str(){
	return ("operator " + value_->str());
}

void StructuredScript::Nodes::OperatorIdentifierNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::OperatorIdentifierNode::attributes(){
	return nullptr;
}

std::string StructuredScript::Nodes::OperatorIdentifierNode::value() const{
	auto id = dynamic_cast<IIdentifierNode *>(value_.get());
	return (id == nullptr) ? value_->str() : id->value();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::OperatorIdentifierNode::nodeValue(){
	return value_;
}

StructuredScript::IStorage *StructuredScript::Nodes::OperatorIdentifierNode::resolveStorage(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Nodes::OperatorIdentifierNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::OperatorIdentifierNode::resolveMemory(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	IType::Ptr type;
	return resolveMemory_(type, storage, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Nodes::OperatorIdentifierNode::addMemory(IStorage *storage){
	if (storage == nullptr)
		return nullptr;

	auto base = Query::Node::getBaseId(value_);
	if (dynamic_cast<IIdentifierNode *>(base.get()) == nullptr)
		return nullptr;

	if (dynamic_cast<ITypeIdentifierNode *>(value_.get()) == nullptr && dynamic_cast<ITypeIdentifierNode *>(base.get()) == nullptr)
		return storage->addOperatorMemory(value_->str());

	auto resolver = dynamic_cast<ITypeResolver *>(value_.get());
	auto type = (resolver == nullptr) ? nullptr : resolver->resolveType(storage);

	return (type == nullptr) ? nullptr : storage->addTypenameOperatorMemory(type);
}

StructuredScript::IMemory::Ptr *StructuredScript::Nodes::OperatorIdentifierNode::addNonOperatorMemory(IStorage *storage){
	return nullptr;
}

bool StructuredScript::Nodes::OperatorIdentifierNode::use(IPureStorage *target, IStorage *storage){
	IType::Ptr type;
	auto memory = resolveMemory_(type, storage, IStorage::SEARCH_DEFAULT);
	if (memory == nullptr)
		return false;

	return (type == nullptr) ? target->useOperator(value_->str(), memory) : target->useTypenameOperator(type, memory);
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::OperatorIdentifierNode::resolveMemory_(IType::Ptr &type, IStorage *storage, unsigned short searchScope){
	if (storage == nullptr)
		return nullptr;

	auto base = Query::Node::getBaseId(value_);
	if (dynamic_cast<IIdentifierNode *>(base.get()) == nullptr)
		return nullptr;

	if (dynamic_cast<ITypeIdentifierNode *>(value_.get()) == nullptr && dynamic_cast<ITypeIdentifierNode *>(base.get()) == nullptr)
		return storage->findOperatorMemory(value_->str(), searchScope);

	auto resolver = dynamic_cast<ITypeResolver *>(value_.get());
	type = (resolver == nullptr) ? nullptr : resolver->resolveType(storage);

	return (type == nullptr) ? nullptr : storage->findTypenameOperatorMemory(type, searchScope);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::PrimitiveTypeIdentifierNode::clone(){
	return std::make_shared<PrimitiveTypeIdentifierNode>(IdentifierNode::str());
}

StructuredScript::IStorage *StructuredScript::Nodes::PrimitiveTypeIdentifierNode::resolveStorage(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	if (storage == nullptr)
		return nullptr;

	auto type = dynamic_cast<IStorage *>(IGlobalStorage::globalStorage)->findType(value_, searchScope);
	return dynamic_cast<IStorage *>(type.get());
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::PrimitiveTypeIdentifierNode::resolveMemory(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Nodes::PrimitiveTypeIdentifierNode::addMemory(IStorage *storage){
	return nullptr;
}

StructuredScript::IMemory::Ptr *StructuredScript::Nodes::PrimitiveTypeIdentifierNode::addNonOperatorMemory(IStorage *storage){
	return nullptr;
}

bool StructuredScript::Nodes::PrimitiveTypeIdentifierNode::use(IPureStorage *target, IStorage *storage){
	return false;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TypenameIdentifierNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TypenameIdentifierNode::clone(){
	return std::make_shared<TypenameIdentifierNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::TypenameIdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = (storage == nullptr) ? nullptr : storage->findType(value(), IStorage::SEARCH_DEFAULT);
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename!", expr)));
	}

	return PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::TypenameIdentifierNode::str(){
	return ("typename " + value_->str());
}

void StructuredScript::Nodes::TypenameIdentifierNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::TypenameIdentifierNode::attributes(){
	return nullptr;
}

std::string StructuredScript::Nodes::TypenameIdentifierNode::value() const{
	auto id = dynamic_cast<IIdentifierNode *>(value_.get());
	return (id == nullptr) ? value_->str() : id->value();
}

StructuredScript::IStorage *StructuredScript::Nodes::TypenameIdentifierNode::resolveStorage(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto type = resolveType(storage, searchScope);
	return (type == nullptr || type->storage() == nullptr) ? nullptr : dynamic_cast<IStorage *>(type.get());
}

StructuredScript::IType::Ptr StructuredScript::Nodes::TypenameIdentifierNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	return (storage == nullptr) ? nullptr : storage->findType(value(), searchScope);
}

bool StructuredScript::Nodes::TypenameIdentifierNode::use(IPureStorage *target, IStorage *storage){
	auto type = resolveType(storage);
	return (type == nullptr) ? false : target->use(value(), type);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TemplatedTypenameIdentifierNode::clone(){
	return std::make_shared<TemplatedTypenameIdentifierNode>(TypenameIdentifierNode::value_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::TemplatedTypenameIdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = resolveType(storage);
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename!", expr)));
	}

	return PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::TemplatedTypenameIdentifierNode::str(){
	return (TypenameIdentifierNode::value_->str() + "<" + value_->str() + ">");
}

StructuredScript::IType::Ptr StructuredScript::Nodes::TemplatedTypenameIdentifierNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto type = TypenameIdentifierNode::resolveType(storage, searchScope);
	if (type == nullptr)
		return nullptr;

	if (type->name() == "any"){//Composite type
		Query::Node::ListType list;
		Query::Node::split(",", value_, list);

		CompositeType::ListType types;
		for (auto node : list){//Resolve type list
			auto resolver = dynamic_cast<ITypeResolver *>(node.get());
			auto value = (resolver == nullptr) ? nullptr : resolver->resolveType(storage, searchScope);
			if (value == nullptr)//Could not resolve type
				return nullptr;

			types.push_back(value);
		}

		return std::make_shared<CompositeType>(types);
	}

	return nullptr;
}

bool StructuredScript::Nodes::TemplatedTypenameIdentifierNode::use(IPureStorage *target, IStorage *storage){
	return false;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ModifiedTypenameIdentifierNode::clone(){
	return std::make_shared<ModifiedTypenameIdentifierNode>(TypenameIdentifierNode::value_->clone(), value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ModifiedTypenameIdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = resolveType(storage);
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename!", expr)));
	}

	return PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::ModifiedTypenameIdentifierNode::str(){
	return (value_.str() + " " + TypenameIdentifierNode::value_->str());
}

void StructuredScript::Nodes::ModifiedTypenameIdentifierNode::states(unsigned short value){
	value_ = value;
}

StructuredScript::IStorage *StructuredScript::Nodes::ModifiedTypenameIdentifierNode::resolveStorage(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto type = TypenameIdentifierNode::resolveType(storage, searchScope);
	return (type == nullptr || type->storage() == nullptr) ? nullptr : dynamic_cast<IStorage *>(type.get());
}

unsigned short StructuredScript::Nodes::ModifiedTypenameIdentifierNode::states() const{
	return value_.states();
}

StructuredScript::IType::Ptr StructuredScript::Nodes::ModifiedTypenameIdentifierNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto type = TypenameIdentifierNode::resolveType(storage, searchScope);
	return (type == nullptr) ? nullptr : std::make_shared<DeclaredType>(type, value_);
}

bool StructuredScript::Nodes::ModifiedTypenameIdentifierNode::use(IPureStorage *target, IStorage *storage){
	return false;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ExpandedTypenameIdentifierNode::clone(){
	return std::make_shared<ExpandedTypenameIdentifierNode>(TypenameIdentifierNode::value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ExpandedTypenameIdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = resolveType(storage);
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename!", expr)));
	}

	return PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::ExpandedTypenameIdentifierNode::str(){
	return (value_->str() + "...");
}

StructuredScript::IType::Ptr StructuredScript::Nodes::ExpandedTypenameIdentifierNode::resolveType(IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto type = TypenameIdentifierNode::resolveType(storage, searchScope);
	return (type == nullptr) ? nullptr : std::make_shared<ExpandedType>(type);
}

bool StructuredScript::Nodes::ExpandedTypenameIdentifierNode::use(IPureStorage *target, IStorage *storage){
	return false;
}
