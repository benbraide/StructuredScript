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

	auto str = str_(value, storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

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

std::string StructuredScript::Nodes::EchoNode::str_(IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr){
	value = value->base();
	if (value == nullptr || Query::Object::isUndefined(value) || Query::Object::isExpansion(value) || Query::Object::isExpanded(value)){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Cannot echo an invalid object!", expr)));

		return "";
	}

	auto enumObject = dynamic_cast<IEnum *>(value.get());
	if (enumObject != nullptr)
		return enumObject->name();

	auto arrayObject = dynamic_cast<IArrayObject *>(value.get());
	if (arrayObject != nullptr){
		std::string str;
		for (auto entry : arrayObject->list()){
			auto entryStr = str_(entry.value, storage, exception, expr);
			if (Query::ExceptionManager::has(exception))
				return "";

			if (str.empty())
				str = entryStr;
			else
				str += ", " + entryStr;
		}

		return ("[" + str + "]");
	}

	auto rangeObject = dynamic_cast<IRange *>(value.get());
	if (rangeObject != nullptr)
		return rangeObject->str();

	auto nodeObject = dynamic_cast<INodeObject *>(value.get());
	if (nodeObject != nullptr){
		auto nodeValue = nodeObject->value();
		return (nodeValue == nullptr) ? value->str(storage, exception, expr) : ("`" + nodeValue->str() + "`");
	}

	auto str = value->str(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return "";

	if (dynamic_cast<IString *>(value.get()) != nullptr)
		return ("\"" + str + "\"");
	if (dynamic_cast<Objects::Char *>(value.get()) != nullptr)
		return ("\'" + str + "\'");
	if (dynamic_cast<Objects::UChar *>(value.get()) != nullptr)
		return ("\'" + str + "\'U");
	if (dynamic_cast<Objects::Short *>(value.get()) != nullptr)
		return (str + "H");
	if (dynamic_cast<Objects::UShort *>(value.get()) != nullptr)
		return (str + "UH");
	if (dynamic_cast<Objects::UInt *>(value.get()) != nullptr)
		return (str + "U");
	if (dynamic_cast<Objects::Long *>(value.get()) != nullptr || dynamic_cast<Objects::LDouble *>(value.get()) != nullptr)
		return (str + "L");
	if (dynamic_cast<Objects::ULong *>(value.get()) != nullptr)
		return (str + "UL");
	if (dynamic_cast<Objects::LLong *>(value.get()) != nullptr)
		return (str + "LL");
	if (dynamic_cast<Objects::ULLong *>(value.get()) != nullptr)
		return (str + "ULL");
	if (dynamic_cast<Objects::Float *>(value.get()) != nullptr)
		return (str + "F");

	return str;
}
