#include "DeclarationNode.h"

StructuredScript::IAny::Ptr StructuredScript::Nodes::SharedDeclaration::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto memory = allocate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	auto object = memory->object();
	if (object != nullptr){//Expansions are only allowed as function parameters
		memory->storage()->remove(memory);//Rollback
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Expansions are only allowed as function parameters!", expr)));
	}

	auto type = memory->type();
	Storage::MemoryState states((type == nullptr) ? Storage::MemoryState::STATE_NONE : type->states());
	if (states.isConstant() || states.isFinal() || states.isReference() || states.isRValReference()){
		memory->storage()->remove(memory);//Rollback
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Declaration requires initialization!", expr)));
	}

	auto backdoor = dynamic_cast<IMemoryBackdoor *>(memory.get());
	if (backdoor == nullptr){
		memory->storage()->remove(memory);//Rollback
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Failed to define object!", expr)));
	}

	backdoor->assign(PrimitiveFactory::createUndefined());
	return memory->object();
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::SharedDeclaration::allocate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = resolveType_(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	auto value = this->value();
	if (value == nullptr)//Unnamed declaration
		return createMemory_(nullptr, storage, type);

	auto adder = dynamic_cast<IMemoryAdder *>(value.get());
	if (adder == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Expected identifier after typename!", expr)));

		return nullptr;
	}

	auto info = adder->addNonOperatorMemory(storage);
	if (info == nullptr || dynamic_cast<IFunctionMemory *>(info->memory.get()) != nullptr){//Failed to add memory
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not allocate memory!", expr)));

		return nullptr;
	}

	return (info->memory = createMemory_(info, storage, type));
}

StructuredScript::IType::Ptr StructuredScript::Nodes::SharedDeclaration::resolveType_(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto typeNode = this->type();
	auto classNode = dynamic_cast<IClassNode *>(typeNode.get());
	if (classNode == nullptr){//Resolve
		auto type = Query::Node::resolveAsType(typeNode, storage);
		if (type == nullptr){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename '" + typeNode->str() + "'!", expr)));

			return nullptr;
		}

		return type;
	}

	return classNode->create(storage, exception, expr);
}

StructuredScript::IMemory::Ptr StructuredScript::Nodes::SharedDeclaration::createMemory_(IStorage::MemoryInfo *info, IStorage *storage, IType::Ptr type){
	auto expandedType = dynamic_cast<IExpandedType *>(type.get());
	if (expandedType == nullptr)
		return std::make_shared<Storage::Memory>(info, storage, type, attributes());

	auto expansion = std::make_shared<Objects::Expansion>(dynamic_cast<IStackedType *>(expandedType)->value());
	auto memory = std::make_shared<Storage::Memory>(info, storage, type, attributes());
	memory->assign(expansion);

	return memory;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DeclarationNode::clone(){
	if (value_ == nullptr)//Unnamed declaration
		return std::make_shared<DeclarationNode>(type_->clone(), nullptr, attributes_);

	return std::make_shared<DeclarationNode>(type_->clone(), value_->clone(), attributes_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::DeclarationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return SharedDeclaration::evaluate(storage, exception, expr);
}

std::string StructuredScript::Nodes::DeclarationNode::str(){
	auto value = (attributes_ == nullptr) ? "" : attributes_->str();
	if (value.empty())
		value = type_->str();
	else
		value += ("\n" + type_->str());

	if (value_ != nullptr){
		if (value.empty())
			value = value_->str();
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

StructuredScript::Interfaces::MemoryAttributes::Ptr StructuredScript::Nodes::DeclarationNode::attributes(){
	return attributes_;
}

std::string StructuredScript::Nodes::DeclarationNode::declName(){
	return (value_ == nullptr) ? "" : value_->str();
}

void StructuredScript::Nodes::DeclarationNode::attributes(IMemoryAttributes::Ptr value){
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

void StructuredScript::Nodes::CommonDeclaration::attributes(IMemoryAttributes::Ptr value){
	declaration_->attributes(value);
}

std::string StructuredScript::Nodes::CommonDeclaration::declName(){
	auto value = this->value();
	return (value == nullptr) ? "" : value->str();
}

StructuredScript::Interfaces::MemoryAttributes::Ptr StructuredScript::Nodes::CommonDeclaration::attributes(){
	return declaration_->attributes();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::InitializationNode::clone(){
	return std::make_shared<InitializationNode>(declaration_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::InitializationNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto memory = allocate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
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

	memory->assign(value, storage, exception, expr);
	if (Query::ExceptionManager::has(exception)){
		memory->storage()->remove(memory);//Rollback
		return nullptr;
	}

	return PrimitiveFactory::createUndefined();
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

	auto memory = declaration->allocate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	auto object = memory->object();
	if (object != nullptr){//Expansions cannot have initializers
		memory->storage()->remove(memory);//Rollback
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Expansions cannot have initializers!", expr)));

		return nullptr;
	}

	return memory;
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

StructuredScript::Interfaces::MemoryAttributes::Ptr StructuredScript::Nodes::DependentDeclarationNode::attributes(){
	return CommonDeclaration::attributes();
}
