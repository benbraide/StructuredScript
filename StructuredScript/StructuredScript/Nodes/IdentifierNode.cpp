#include "IdentifierNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IdentifierNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IdentifierNode::clone(){
	return std::make_shared<IdentifierNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::IdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto memory = (storage == nullptr) ? nullptr : storage->findMemory(value_, IStorage::SEARCH_DEFAULT);
	if (memory == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve identifier!", expr)));
	}

	return memory->object();
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
	if (storage == nullptr)
		return nullptr;

	auto id = dynamic_cast<IIdentifierNode *>(value_.get());
	if (id == nullptr)
		return nullptr;

	if (dynamic_cast<ITypeIdentifierNode *>(id) == nullptr)
		return storage->findOperatorMemory(id->value(), searchScope);

	return storage->findTypenameOperatorMemory(id->value(), searchScope);
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
