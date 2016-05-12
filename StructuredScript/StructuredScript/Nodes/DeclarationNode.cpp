#include "DeclarationNode.h"

StructuredScript::IAny::Ptr StructuredScript::Nodes::SharedDeclaration::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto memory = allocate(storage, exception, expr);
	return (memory == nullptr) ? nullptr : memory->object();
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::SharedDeclaration::allocate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = Query::Node::resolveAsType(this->type(), storage);
	if (type == nullptr){
		if (storage == nullptr){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not allocate memory!", expr)));
		}
		else{
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename '" + this->type()->str() + "'!", expr)));
		}

		return nullptr;
	}

	auto value = this->value();
	if (value == nullptr)//Unnamed declaration
		return std::make_shared<Storage::TempMemory>(storage, PrimitiveFactory::createUndefined());

	if (!Query::Node::isIdentifier(value) || Query::Node::isTypeIdentifier(value)){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Expected identifier after typename!", expr)));
	}

	IMemory::Ptr *memory;
	auto operatorId = dynamic_cast<IOperatorIdentifierNode *>(value.get());
	if (operatorId != nullptr){//Add operator memory
		auto nodeValue = operatorId->nodeValue();
		if (dynamic_cast<ITypeIdentifierNode *>(nodeValue.get()) == nullptr)//General operator
			memory = storage->addOperatorMemory(dynamic_cast<IIdentifierNode *>(value.get())->value());
		else//Typename operator
			memory = storage->addTypenameOperatorMemory(dynamic_cast<IIdentifierNode *>(value.get())->value());
	}
	else//Add general memory
		memory = storage->addMemory(dynamic_cast<IIdentifierNode *>(value.get())->value());

	if (memory == nullptr){//Failed to add memory
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not allocate memory!", expr)));

		return nullptr;
	}

	auto state = Storage::MemoryState(states());
	auto attributes = dynamic_cast<Storage::MemoryAttributes *>(this->attributes());
	if (attributes == nullptr){//Unknown error
		storage->remove(*memory);//Rollback
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad declaration!", expr)));

		return nullptr;
	}

	if (operatorId != nullptr)//Operator memory
		return (*memory = std::make_shared<Storage::FunctionMemory>(storage, type, state, *attributes));

	return (*memory = std::make_shared<Storage::Memory>(storage, PrimitiveFactory::createUndefined(), type, state, *attributes));
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::clone(){
	if (value_ == nullptr)//Unnamed declaration
		return std::make_shared<DeclarationNode>(type_->clone(), nullptr, state_, attributes_);

	return std::make_shared<DeclarationNode>(type_->clone(), value_->clone(), state_, attributes_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::DeclarationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return SharedDeclaration::evaluate(storage, exception, expr);
}

std::string StructuredScript::Nodes::DeclarationNode::str(){
	auto value = attributes_.str();
	if (value.empty())
		value = state_.str();
	else
		value += ("\n" + state_.str());

	if (value.empty() || *value.rbegin() == '\n')
		value += type_->str();
	else
		value += (" " + type_->str());

	if (value_ != nullptr){
		if (value.empty())
			value += value_->str();
		else
			value += (" " + value_->str());
	}

	return value;
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::DeclarationNode::allocate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return SharedDeclaration::allocate(storage, exception, expr);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::type(){
	return type_;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::value(){
	return value_;
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

StructuredScript::Nodes::CommonDeclaration::CommonDeclaration(Ptr declaration, Ptr value)
	: declaration_(declaration), value_(value){}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::CommonDeclaration::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::CommonDeclaration::type(){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	return (declaration == nullptr) ? nullptr : declaration->type();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::CommonDeclaration::value(){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	return (declaration == nullptr) ? nullptr : declaration->value();
}

void StructuredScript::Nodes::CommonDeclaration::states(unsigned short value){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	if (declaration != nullptr)
		declaration->states(value);
}

unsigned short StructuredScript::Nodes::CommonDeclaration::states(){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	return (declaration == nullptr) ? 0 : declaration->states();
}

void StructuredScript::Nodes::CommonDeclaration::attributes(const Storage::MemoryAttributes &value){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	if (declaration != nullptr)
		declaration->attributes(value);
}

StructuredScript::IMemoryAttributes *StructuredScript::Nodes::CommonDeclaration::attributes(){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	return (declaration == nullptr) ? nullptr : declaration->attributes();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::InitializationNode::clone(){
	return std::make_shared<InitializationNode>(declaration_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::InitializationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	if (declaration == nullptr){//Declaration is required
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad initialization!", expr)));
	}

	auto memory = declaration->allocate(storage, exception, expr);
	if (memory == nullptr)
		return nullptr;

	if (dynamic_cast<IFunctionMemory *>(memory.get()) != nullptr){
		memory->storage()->remove(memory);//Rollback
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad initialization!", expr)));
	}

	auto value = value_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception)){
		memory->storage()->remove(memory);//Rollback
		return nullptr;
	}

	if (Query::Object::isUndefined(value)){
		memory->storage()->remove(memory);//Rollback
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad initialization!", expr)));

		return nullptr;
	}

	auto undefined = memory->object();
	memory->assign(value, exception, expr);
	if (Query::ExceptionManager::has(exception)){
		memory->storage()->remove(memory);//Rollback
		return nullptr;
	}

	return undefined;
}

std::string StructuredScript::Nodes::InitializationNode::str(){
	return (declaration_->str() + " = " + value_->str());
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::InitializationNode::allocate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto declaration = dynamic_cast<IDeclarationNode *>(declaration_.get());
	if (declaration == nullptr){//Declaration is required
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad initialization!", expr)));
	}

	return declaration->allocate(storage, exception, expr);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DependentDeclarationNode::clone(){
	return std::make_shared<DependentDeclarationNode>(declaration_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::DependentDeclarationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (dynamic_cast<IDeclarationNode *>(declaration_.get()) == nullptr){//Declaration is required
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad declaration!", expr)));
	}

	declaration_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return SharedDeclaration::evaluate(storage, exception, expr);
}

std::string StructuredScript::Nodes::DependentDeclarationNode::str(){
	return (declaration_->str() + ", " + value_->str());
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::DependentDeclarationNode::allocate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (dynamic_cast<IDeclarationNode *>(declaration_.get()) == nullptr){//Declaration is required
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Bad declaration!", expr)));

		return nullptr;
	}

	declaration_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	return SharedDeclaration::allocate(storage, exception, expr);
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DependentDeclarationNode::type(){
	return CommonDeclaration::type();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DependentDeclarationNode::value(){
	return value_;
}

unsigned short StructuredScript::Nodes::DependentDeclarationNode::states(){
	return CommonDeclaration::states();
}

StructuredScript::IMemoryAttributes *StructuredScript::Nodes::DependentDeclarationNode::attributes(){
	return CommonDeclaration::attributes();
}
