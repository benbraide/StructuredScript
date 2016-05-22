#include "TypeOfNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TypeOfNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TypeOfNode::clone(){
	return std::make_shared<TypeOfNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::TypeOfNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto value = value_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	auto type = value->type();
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Target has no type!", expr)));
	}

	return PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::TypeOfNode::str(){
	return ("typeof " + value_->str());
}

void StructuredScript::Nodes::TypeOfNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::TypeOfNode::attributes(){
	return nullptr;
}
