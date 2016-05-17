#include "ThrowNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ThrowNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ThrowNode::clone(){
	return std::make_shared<ThrowNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ThrowNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (exception == nullptr || Query::ExceptionManager::has(exception))
		return nullptr;

	if (!Query::Node::isEmpty(value_)){//Throw new
		auto value = value_->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		value = value->base();
		if (value == nullptr || Query::Object::isUndefined(value) || Query::Object::isExpansion(value) || Query::Object::isExpanded(value)){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"Cannot throw an invalid object!", expr)));
		}

		return Query::ExceptionManager::setAndReturnObject(exception, value);
	}

	if (!exception->unsuppress()){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'throw': Used outside 'catch' and 'finally'!", expr)));
	}

	return nullptr;
}

std::string StructuredScript::Nodes::ThrowNode::str(){
	return Query::Node::isEmpty(value_) ? "throw" : ("throw " + value_->str());
}

void StructuredScript::Nodes::ThrowNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::ThrowNode::attributes(){
	return nullptr;
}
