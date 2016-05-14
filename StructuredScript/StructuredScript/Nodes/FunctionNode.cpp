#include "FunctionNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionNode::ptr(){
	return shared_from_this();
}

std::string StructuredScript::Nodes::FunctionNode::str(){
	return (declaration_->str() + "(" + parameters_->str() + ")");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionNode::type(){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	return (declaration == nullptr) ? nullptr : declaration->type();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionNode::name(){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	return (declaration == nullptr) ? nullptr : declaration->value();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionNode::parameters(){
	return parameters_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionDeclarationNode::clone(){
	return std::make_shared<FunctionDeclarationNode>(declaration_->clone(), parameters_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::FunctionDeclarationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	if (declaration == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad function declaration!", expr)));
	}

	return nullptr;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionDefinitionNode::clone(){
	return std::make_shared<FunctionDefinitionNode>(declaration_->clone(), parameters_->clone(), definition_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::FunctionDefinitionNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	if (declaration == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad function definition!", expr)));
	}

	auto type = Query::Node::resolveAsType(declaration->type(), storage);
	if (type == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve return type!", expr)));
	}

	auto name = declaration->value();
	if (name == nullptr || !Query::Node::isIdentifier(name) || Query::Node::isTypeIdentifier(name) || Query::Node::isOperatorIdentifier(name)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Expected identifier after typename!", expr)));
	}

	auto memory = storage->addMemory(dynamic_cast<IIdentifierNode *>(name.get())->value());
	if (memory == nullptr){//Failed to add memory
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not allocate memory!", expr)));
	}

	if (*memory == nullptr)//Create new function memory
		*memory = std::make_shared<Storage::FunctionMemory>(storage);

	auto function = std::make_shared<Objects::Function>(type, parameters_, definition_);
	if (!function->init(storage, exception, expr)){//Error
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Failed to define function!", expr)));
	}

	dynamic_cast<IFunctionMemory *>(memory->get())->add(function, declaration->attributes());
	return function;
}

std::string StructuredScript::Nodes::FunctionDefinitionNode::str(){
	return (declaration_->str() + "(" + parameters_->str() + "){...}");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionDefinitionNode::definition(){
	return definition_;
}