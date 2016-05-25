#include "EnumNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::EnumNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::EnumNode::clone(){
	return std::make_shared<EnumNode>(name_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::EnumNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto id = dynamic_cast<IIdentifierNode *>(name_.get());
	if (id == nullptr || Query::Node::isOperatorIdentifier(name_) || Query::Node::isTypeIdentifier(name_)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + name_->str() + "': Expected an identifier!", expr)));
	}

	auto idValue = id->value();
	auto index = 0;

	auto type = std::make_shared<Type>(storage, idValue);
	auto declType = std::make_shared<DeclaredType>(type, Storage::MemoryState(Storage::MemoryState::STATE_STATIC));

	Query::Node::ListType list;
	Query::Node::split(",", value_, list);
	for (auto item : list){//Add entries to type
		id = dynamic_cast<IIdentifierNode *>(item.get());
		if (id == nullptr || Query::Node::isOperatorIdentifier(item) || Query::Node::isTypeIdentifier(item)){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + item->str() + "': Expected an identifier!", expr)));
		}

		auto info = type->addMemory(id->value());
		if (info == nullptr){//Duplicate
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + item->str() + "': Duplicate entry found!", expr)));
		}

		//Add static memory
		auto value = PrimitiveFactory::createEnum(type, id->value(), index++);
		auto memory = std::make_shared<Storage::Memory>(info, storage, declType, nullptr);

		memory->assign(value);
		info->memory = memory;
		value->setMemory(nullptr);//Disable reference
	}

	auto added = storage->addType(idValue);
	if (added == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Failed to create enum!", expr)));
	}

	*added = type;//Assign value

	return PrimitiveFactory::createUndefined();
}

std::string StructuredScript::Nodes::EnumNode::str(){
	return ("enum " + name_->str() + "{...}");
}

void StructuredScript::Nodes::EnumNode::attributes(IMemoryAttributes::Ptr attributes){}

std::string StructuredScript::Nodes::EnumNode::declName(){
	return name_->str();
}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::EnumNode::attributes(){
	return nullptr;
}
