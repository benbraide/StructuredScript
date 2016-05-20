#include "PropertyNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::PropertyNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::PropertyNode::clone(){
	return std::make_shared<PropertyNode>(declaration_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::PropertyNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	if (declaration == nullptr){//Declaration is required
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad property definition!", expr)));
	}

	auto memory = declaration->allocate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	Query::Node::ListType lines;
	Query::Node::split(";", value_, lines);

	auto type = std::make_shared<Type>(storage, "");//Create an anonymous type
	for (auto line : lines){
		line->evaluate(type.get(), exception, expr);
		if (Query::ExceptionManager::has(exception)){
			memory->storage()->remove(memory);//Rollback
			return nullptr;
		}
	}

	auto backdoor = dynamic_cast<IMemoryBackdoor *>(memory.get());
	if (backdoor == nullptr){
		memory->storage()->remove(memory);//Rollback
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Failed to define property!", expr)));
	}

	backdoor->assign(std::make_shared<Objects::Property>(type));
	return PrimitiveFactory::createUndefined();
}

std::string StructuredScript::Nodes::PropertyNode::str(){
	return (declaration_->str() + "{...}");
}

void StructuredScript::Nodes::PropertyNode::attributes(IMemoryAttributes::Ptr attributes){
	attributes_ = attributes;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::PropertyNode::declaration(){
	return declaration_;
}

std::string StructuredScript::Nodes::PropertyNode::declName(){
	auto value = dynamic_cast<IDeclarationNode *>(declaration_.get())->value();
	return (value == nullptr) ? "" : value->str();
}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::PropertyNode::attributes(){
	return attributes_;
}
