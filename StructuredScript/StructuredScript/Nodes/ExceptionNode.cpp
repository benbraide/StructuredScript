#include "ExceptionNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TryNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::TryNode::clone(){
	return std::make_shared<TryNode>(handler_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::TryNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (Query::Node::isEmpty(value_))
		return PrimitiveFactory::createUndefined();

	Storage::Storage localStorage(storage);
	value_->evaluate(&localStorage, exception, expr);
	if (!Query::ExceptionManager::has(exception))
		return PrimitiveFactory::createUndefined();

	exception->suppress();
	handler_->evaluate(storage, exception, expr);//Evaluate matching 'catch'

	auto handler = dynamic_cast<IExceptionHandler *>(handler_.get());
	if (handler != nullptr)//Evaluate 'finally'
		handler->finally(storage, exception, expr);

	exception->unsuppress();//Unsuppress unhandled exception

	return PrimitiveFactory::createUndefined();
}

std::string StructuredScript::Nodes::TryNode::str(){
	return ("try {...}" + handler_->str());
}

void StructuredScript::Nodes::TryNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::TryNode::attributes(){
	return nullptr;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::CatchNode::clone(){
	if (next_ == nullptr)
		return std::make_shared<CatchNode>(predicate_->clone(), value_->clone(), nullptr);
	return std::make_shared<CatchNode>(predicate_->clone(), value_->clone(), next_->clone());
}

std::string StructuredScript::Nodes::CatchNode::str(){
	return ("catch (" + predicate_->str() + "){...}");
}

void StructuredScript::Nodes::CatchNode::finally(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto handler = dynamic_cast<IExceptionHandler *>(next_.get());
	if (handler != nullptr)//Try next
		handler->finally(storage, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::CatchNode::evaluate_(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto memory = dynamic_cast<IDeclarationNode *>(predicate_.get())->allocate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (memory->object() != nullptr){//Expansions cannot have initializers
		memory->storage()->remove(memory);//Rollback
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Expansions cannot be used as 'catch' targets!", expr)));
	}

	memory->assign(exception->get(), storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	NonIteratorNode::evaluate_(storage, exception, expr);
	if (!Query::ExceptionManager::has(exception))
		exception->clear();//Clear handled exception

	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::CatchNode::else_(IStorage *storage, IExceptionManager *exception, INode *expr){
	return (next_ == nullptr) ? nullptr : next_->evaluate(storage, exception, expr);
}

bool StructuredScript::Nodes::CatchNode::truth_(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto declaration = dynamic_cast<IDeclarationNode *>(predicate_.get());
	if (declaration == nullptr)
		return false;

	auto e = Query::ExceptionManager::get(exception);
	if (e == nullptr)
		return false;

	/*
	void e(any v){try{throw v}catch(bool){echo"bool"}catch(char){echo"char"}catch(int){echo"int"}catch(long){echo"long"}catch(long long){echo"long long"}catch(float){echo"float"}catch(double){echo"double"}catch(long double){echo"long double"}catch(string){echo"string"}catch(any){echo"any"}finally{echo"finally"}}
	*/

	auto declType = Query::Node::resolveAsType(declaration->type(), storage);
	return (declType != nullptr && declType->isCompatibleWith(e->type(), true));
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FinallyNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::FinallyNode::clone(){
	return std::make_shared<FinallyNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::FinallyNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	return PrimitiveFactory::createUndefined();//Responds only to 'finally()'
}

std::string StructuredScript::Nodes::FinallyNode::str(){
	return "finally {...}";
}

void StructuredScript::Nodes::FinallyNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::FinallyNode::attributes(){
	return nullptr;
}

void StructuredScript::Nodes::FinallyNode::finally(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (Query::Node::isEmpty(value_))
		return;

	ExceptionManager xManager;
	value_->evaluate(storage, &xManager, expr);
	if (xManager.has())//Forward exception
		exception->set(xManager.get());
}
