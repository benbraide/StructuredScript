#include "IndexNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IndexNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IndexNode::clone(){
	return std::make_shared<IndexNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::IndexNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto object = std::make_shared<Objects::ArrayObject>();

	Query::Node::ListType entries;
	Query::Node::split(",", value_, entries);

	for (auto entry : entries){
		auto value = entry->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		object->append(value, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	return object;
}

std::string StructuredScript::Nodes::IndexNode::str(){
	return ("[" + value_->str() + "]");
}

void StructuredScript::Nodes::IndexNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::IndexNode::attributes(){
	return nullptr;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IndexNode::value(){
	return value_;
}
