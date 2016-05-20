#include "NewNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::NewNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::NewNode::clone(){
	return std::make_shared<NewNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::NewNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	Ptr target, args;
	
	auto binary = dynamic_cast<IBinaryOperatorNode *>(value_.get());
	if (binary != nullptr){
		if (binary->value() != "()"){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + str() + "...': Bad expression!", expr)));
		}

		target = binary->leftOperand();
		args = binary->rightOperand();
	}
	else{//Unary | None
		auto unary = dynamic_cast<IUnaryOperatorNode *>(value_.get());
		if (unary != nullptr){
			if (unary->isLeft() || unary->value() != "()"){
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + str() + "...': Bad expression!", expr)));
			}

			target = unary->operand();
		}
		else//Node
			target = value_;
	}

	auto type = Query::Node::resolveAsType(target, storage);
	if (type == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + str() + "': Could not resolve typename '" + target->str() + "'!", expr)));

		return nullptr;
	}

	auto classType = dynamic_cast<IClass *>(type.get());
	if (classType == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + target->str() + "': Type cannot be instantiated with 'new'!", expr)));

		return nullptr;
	}

	auto object = classType->create(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	IFunction::ArgListType list;
	if (args != nullptr){
		Storage::FunctionMemory::resolveArgList(args, list, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	dynamic_cast<IObject *>(object.get())->construct(list, storage, exception, expr);
	return Query::ExceptionManager::has(exception) ? nullptr : object;
}

std::string StructuredScript::Nodes::NewNode::str(){
	return ("new " + value_->str());
}

void StructuredScript::Nodes::NewNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::NewNode::attributes(){
	return nullptr;
}
