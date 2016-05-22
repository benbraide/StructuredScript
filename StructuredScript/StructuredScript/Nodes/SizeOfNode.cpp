#include "SizeOfNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::SizeOfNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::SizeOfNode::clone(){
	return std::make_shared<SizeOfNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::SizeOfNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto value = value_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	value = value->base();
	auto number = dynamic_cast<INumber *>(value.get());
	if (number == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'sizeof': Can only be applied to primitive numeric types!", expr)));
	}

	return PrimitiveFactory::createUInt(number->size());
}

std::string StructuredScript::Nodes::SizeOfNode::str(){
	return ("sizeof " + value_->str());
}

void StructuredScript::Nodes::SizeOfNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::SizeOfNode::attributes(){
	return nullptr;
}
