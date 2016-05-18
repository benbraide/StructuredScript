#include "NamespaceNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::NamespaceNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::NamespaceNode::clone(){
	return std::make_shared<NamespaceNode>(name_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::NamespaceNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::Node::ListType list;
	Query::Node::split("::", name_, list);
	
	std::list<IIdentifierNode *> ids;
	for (auto item : list){
		auto id = dynamic_cast<IIdentifierNode *>(item.get());
		if (id == nullptr || Query::Node::isOperatorIdentifier(item) || Query::Node::isTypeIdentifier(item)){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + item->str() + "': Expected an identifier!", expr)));
		}

		ids.push_back(id);
	}

	for (auto id : ids){//Add namespaces separated by '::'
		auto name = id->value();
		auto added = storage->addStorage(name);
		if (added == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + name + "': Failed to add namespace!", expr)));
		}

		if (*added == nullptr)//Add new
			*added = std::make_shared<Storage::Namespace>(storage, name);

		storage = added->get();
	}

	if (!Query::Node::isEmpty(value_)){//Evaluate inside new storage
		value_->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	return PrimitiveFactory::createUndefined();
}

std::string StructuredScript::Nodes::NamespaceNode::str(){
	return ("namespace " + name_->str() + "{...}");
}

void StructuredScript::Nodes::NamespaceNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::NamespaceNode::attributes(){
	return nullptr;
}
