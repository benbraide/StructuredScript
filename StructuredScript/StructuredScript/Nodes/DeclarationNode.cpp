#include "DeclarationNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::clone(){
	if (value_ == nullptr)//Unnamed declaration
		return std::make_shared<DeclarationNode>(type_->clone(), nullptr, state_, attributes_);

	return std::make_shared<DeclarationNode>(type_->clone(), value_->clone(), state_, attributes_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::DeclarationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto memory = allocate(storage, exception, expr);
	return (memory == nullptr) ? nullptr : memory->object();
}

std::string StructuredScript::Nodes::DeclarationNode::str(){
	if (value_ == nullptr)//Unnamed declaration
		return (attributes_.str() + "\n" + state_.str() + " " + type_->str());

	return (attributes_.str() + "\n" + state_.str() + " " + type_->str() + " " + value_->str());
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::DeclarationNode::allocate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = Query::Node::resolveAsType(type_, storage);
	if (type == nullptr){
		if (storage == nullptr){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not allocate memory!", expr)));
		}
		else{
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename '" + type_->str() + "'!", expr)));
		}

		return nullptr;
	}

	if (value_ == nullptr)//Unnamed declaration
		return std::make_shared<Storage::TempMemory>(storage, PrimitiveFactory::createUndefined());

	if (!Query::Node::isIdentifier(value_) || Query::Node::isTypeIdentifier(value_)){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Expected identifier after typename!", expr)));
	}

	IMemory::Ptr *memory;
	auto operatorId = dynamic_cast<IOperatorIdentifierNode *>(value_.get());
	if (operatorId != nullptr){//Add operator memory
		auto value = operatorId->nodeValue();
		if (dynamic_cast<ITypeIdentifierNode *>(value.get()) == nullptr)//General operator
			memory = storage->addOperatorMemory(dynamic_cast<IIdentifierNode *>(value_.get())->value());
		else//Typename operator
			memory = storage->addTypenameOperatorMemory(dynamic_cast<IIdentifierNode *>(value_.get())->value());
	}
	else//Add general memory
		memory = storage->addMemory(dynamic_cast<IIdentifierNode *>(value_.get())->value());

	if (memory == nullptr){//Failed to add memory
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not allocate memory!", expr)));

		return nullptr;
	}

	if (operatorId != nullptr)//Operator memory
		return (*memory = std::make_shared<Storage::FunctionMemory>(storage, type, state_, attributes_));

	return (*memory = std::make_shared<Storage::Memory>(storage, PrimitiveFactory::createUndefined(), type, state_, attributes_));
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::type(){
	return type_;
}

unsigned short StructuredScript::Nodes::DeclarationNode::states(){
	return state_.states();
}

void StructuredScript::Nodes::DeclarationNode::states(unsigned short value){
	state_ = value;
}

StructuredScript::IMemoryAttributes *StructuredScript::Nodes::DeclarationNode::attributes(){
	return &attributes_;
}

void StructuredScript::Nodes::DeclarationNode::attributes(const Storage::MemoryAttributes &value){
	attributes_ = value;
}
