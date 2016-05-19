#include "FunctionNode.h"

StructuredScript::IAny::Ptr StructuredScript::Nodes::CallableNode::evaluate_(INode::Ptr name, IType::Ptr type, INode::Ptr definition,
	IStorage *storage, IExceptionManager *exception, INode *expr){
	auto adder = dynamic_cast<IMemoryAdder *>(name.get());
	if (adder == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Expected identifier after typename!", expr)));
	}

	auto memory = adder->addMemory(storage);
	if (memory == nullptr){//Failed to add memory
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not allocate memory!", expr)));
	}

	if (*memory == nullptr)//Create new function memory
		*memory = std::make_shared<Storage::FunctionMemory>(storage);

	auto function = create_(type, definition);
	auto isRightUnary = (attributes_ == nullptr) ? false : (attributes_->hasAttribute("RightUnary") || attributes_->hasAttribute("UnaryRight"));

	if (!function->init(isRightUnary, (*memory)->storage(), exception, expr)){//Error
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Failed to define function!", expr)));
	}

	if (dynamic_cast<IFunctionMemory *>(memory->get())->add(function, attributes_) == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Cannot duplicate function declaration/definition!", expr)));
	}

	return function;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionNode::ptr(){
	return shared_from_this();
}

std::string StructuredScript::Nodes::FunctionNode::str(){
	return (declaration_->str() + "(" + parameters_->str() + ")");
}

void StructuredScript::Nodes::FunctionNode::attributes(IMemoryAttributes::Ptr attributes){
	attributes_ = attributes;
}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::FunctionNode::attributes(){
	return attributes_;
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

StructuredScript::IAny::Ptr StructuredScript::Nodes::FunctionNode::evaluate_(Ptr definition, IStorage *storage, IExceptionManager *exception, INode *expr){
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

	return CallableNode::evaluate_(declaration->value(), type, definition, storage, exception, expr);
}

std::shared_ptr<StructuredScript::Objects::Function> StructuredScript::Nodes::FunctionNode::create_(IType::Ptr type, INode::Ptr definition){
	return std::make_shared<Objects::Function>(type, parameters_, definition);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionDeclarationNode::clone(){
	return std::make_shared<FunctionDeclarationNode>(declaration_->clone(), parameters_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::FunctionDeclarationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return evaluate_(nullptr, storage, exception, expr);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionDefinitionNode::clone(){
	return std::make_shared<FunctionDefinitionNode>(declaration_->clone(), parameters_->clone(), definition_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::FunctionDefinitionNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return evaluate_(definition_, storage, exception, expr);
}

std::string StructuredScript::Nodes::FunctionDefinitionNode::str(){
	return (declaration_->str() + "(" + parameters_->str() + "){...}");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FunctionDefinitionNode::definition(){
	return definition_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ConstructorNode::type(){
	return nullptr;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ConstructorNode::name(){
	return declaration_;
}

void StructuredScript::Nodes::ConstructorNode::parseInitializers(Ptr initializers, InitializerListType &list, IExceptionManager *exception, INode *expr){
	Query::Node::ListType splitList;
	Query::Node::split(",", initializers, splitList);

	for (auto initializer : splitList){// target(value...), ...
		auto binary = dynamic_cast<IBinaryOperatorNode *>(initializer.get());
		if (binary == nullptr || binary->value() != "()"){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + initializer->str() + "': Bad constructor initializer!", expr)));

			return;
		}

		auto target = binary->leftOperand();
		auto id = dynamic_cast<IIdentifierNode *>(target.get());
		if (id == nullptr || Query::Node::isOperatorIdentifier(target) || Query::Node::isTypeIdentifier(target)){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + initializer->str() + "': Bad constructor initializer!", expr)));

			return;
		}

		list[id->value()] = binary->rightOperand();
	}
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ConstructorNode::evaluate_(Ptr definition, IStorage *storage, IExceptionManager *exception, INode *expr){
	return CallableNode::evaluate_(declaration_, nullptr, definition, storage, exception, expr);
}

std::shared_ptr<StructuredScript::Objects::Function> StructuredScript::Nodes::ConstructorNode::create_(IType::Ptr type, INode::Ptr definition){
	return std::make_shared<Objects::Constructor>(parameters_, definition, initializers_);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ConstructorDeclarationNode::clone(){
	return std::make_shared<ConstructorDeclarationNode>(declaration_->clone(), parameters_->clone(), initializers_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ConstructorDeclarationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return evaluate_(nullptr, storage, exception, expr);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ConstructorDefinitionNode::clone(){
	return std::make_shared<ConstructorDefinitionNode>(declaration_->clone(), parameters_->clone(), initializers_, definition_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ConstructorDefinitionNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return evaluate_(definition_, storage, exception, expr);
}

std::string StructuredScript::Nodes::ConstructorDefinitionNode::str(){
	return (declaration_->str() + "(" + parameters_->str() + "){...}");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ConstructorDefinitionNode::definition(){
	return definition_;
}
