#include "EchoNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::EchoNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::EchoNode::clone(){
	return std::make_shared<EchoNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::EchoNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto value = value_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	value = value->base();
	if (value == nullptr || Query::Object::isUndefined(value) || Query::Object::isExpansion(value) || Query::Object::isExpanded(value)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Cannot echo an invalid object!", expr)));
	}

	auto str = value->str(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (dynamic_cast<IString *>(value.get()) != nullptr)
		std::cout << "\"" << str << "\"\n";
	else if (dynamic_cast<Objects::Char *>(value.get()) != nullptr)
		std::cout << "\'" << str << "\'\n";
	else if (dynamic_cast<Objects::UChar *>(value.get()) != nullptr)
		std::cout << "\'" << str << "\'U\n";
	else if (dynamic_cast<Objects::Short *>(value.get()) != nullptr)
		std::cout << str << "H\n";
	else if (dynamic_cast<Objects::UShort *>(value.get()) != nullptr)
		std::cout << str << "UH\n";
	else if (dynamic_cast<Objects::UInt *>(value.get()) != nullptr)
		std::cout << str << "U\n";
	else if (dynamic_cast<Objects::Long *>(value.get()) != nullptr || dynamic_cast<Objects::LDouble *>(value.get()) != nullptr)
		std::cout << str << "L\n";
	else if (dynamic_cast<Objects::ULong *>(value.get()) != nullptr)
		std::cout << str << "UL\n";
	else if (dynamic_cast<Objects::LLong *>(value.get()) != nullptr)
		std::cout << str << "LL\n";
	else if (dynamic_cast<Objects::ULLong *>(value.get()) != nullptr)
		std::cout << str << "ULL\n";
	else if (dynamic_cast<Objects::Float *>(value.get()) != nullptr)
		std::cout << str << "F\n";
	else
		std::cout << str << "\n";

	return PrimitiveFactory::createUndefined();
}

std::string StructuredScript::Nodes::EchoNode::str(){
	return ("echo " + value_->str());
}

void StructuredScript::Nodes::EchoNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::EchoNode::attributes(){
	return nullptr;
}
