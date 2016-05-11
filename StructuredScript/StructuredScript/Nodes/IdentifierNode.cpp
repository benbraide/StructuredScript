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

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::PrimitiveTypeIdentifierNode::clone(){
	return std::make_shared<PrimitiveTypeIdentifierNode>(name_, IdentifierNode::str());
}

std::string StructuredScript::Nodes::PrimitiveTypeIdentifierNode::str(){
	return name_;
}
