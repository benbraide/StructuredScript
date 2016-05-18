#include "UseNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::UseNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::UseNode::clone(){
	return std::make_shared<UseNode>(value_->clone(), storage_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::UseNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto pure = dynamic_cast<IPureStorage *>(storage);
	if (pure == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'using': Found in an unsupported scope!", expr)));
	}

	if (storage_){
		auto value = Query::Node::resolveAsStorage(value_, storage);
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"'" + value_->str() + "': Could not resolve expression!", expr)));
		}

		if (!pure->use(value)){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"'using': Found in an unsupported scope!", expr)));
		}
	}

	if (!Query::Node::use(value_, pure, storage)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'using': Could not use expression!", expr)));
	}

	return PrimitiveFactory::createUndefined();
}

std::string StructuredScript::Nodes::UseNode::str(){
	if (storage_)
		return ("using namespace " + value_->str());
	return ("using " + value_->str());
}

void StructuredScript::Nodes::UseNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::UseNode::attributes(){
	return nullptr;
}
