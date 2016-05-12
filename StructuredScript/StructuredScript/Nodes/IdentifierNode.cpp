#include "IdentifierNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IdentifierNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IdentifierNode::clone(){
	return std::make_shared<IdentifierNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::IdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto memory = (storage == nullptr) ? nullptr : storage->findMemory(value_, false);
	if (memory == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve identifier!", expr)));
	}

	auto memoryOwner = memory->storage();
	if (memoryOwner != nullptr){//Validate access

	}

	return memory->object();
}

std::string StructuredScript::Nodes::IdentifierNode::str(){
	return value_;
}

std::string StructuredScript::Nodes::IdentifierNode::value() const{
	return value_;
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

std::string StructuredScript::Nodes::OperatorIdentifierNode::value() const{
	auto id = dynamic_cast<IIdentifierNode *>(value_.get());
	return (id == nullptr) ? value_->str() : id->value();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::OperatorIdentifierNode::nodeValue(){
	return value_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::PrimitiveTypeIdentifierNode::clone(){
	return std::make_shared<PrimitiveTypeIdentifierNode>(name_, IdentifierNode::str());
}

std::string StructuredScript::Nodes::PrimitiveTypeIdentifierNode::str(){
	return name_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TypenameIdentifierNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TypenameIdentifierNode::clone(){
	return std::make_shared<TypenameIdentifierNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::TypenameIdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = (storage == nullptr) ? nullptr : storage->findType(value(), false);
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename!", expr)));
	}

	return PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::TypenameIdentifierNode::str(){
	return ("typename " + value_->str());
}

std::string StructuredScript::Nodes::TypenameIdentifierNode::value() const{
	auto id = dynamic_cast<IIdentifierNode *>(value_.get());
	return (id == nullptr) ? value_->str() : id->value();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TemplatedTypenameIdentifierNode::clone(){
	return std::make_shared<TemplatedTypenameIdentifierNode>(TypenameIdentifierNode::value_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::TemplatedTypenameIdentifierNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = resolve(storage);
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename!", expr)));
	}

	return PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::TemplatedTypenameIdentifierNode::str(){
	return (TypenameIdentifierNode::value_->str() + "<" + value_->str() + ">");
}

StructuredScript::IType::Ptr StructuredScript::Nodes::TemplatedTypenameIdentifierNode::resolve(IStorage *storage){
	auto type = Query::Node::resolveAsType(TypenameIdentifierNode::value_, storage);
	if (type == nullptr)
		return nullptr;

	if (type->name() == "any"){//Composite type
		Query::Node::ListType list;
		Query::Node::split(",", value_, list);

		CompositeType::ListType types;
		for (auto node : list){//Resolve type list
			auto value = Query::Node::resolveAsType(node, storage);
			if (value == nullptr)//Could not resolve type
				return nullptr;

			types.push_back(value);
		}

		return std::make_shared<CompositeType>(types);
	}

	return nullptr;
}
