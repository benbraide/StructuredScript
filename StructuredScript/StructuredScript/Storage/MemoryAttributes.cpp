#include "MemoryAttributes.h"

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Storage::MemoryAttributes::ptr(){
	return shared_from_this();
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::MemoryAttributes::getAttribute(const std::string &name){
	auto attribute = attributes_.find(name);
	return (attribute == attributes_.end()) ? nullptr : attribute->second;
}

bool StructuredScript::Storage::MemoryAttributes::hasAttribute(const std::string &name) const{
	return (attributes_.find(name) != attributes_.end());
}

std::string StructuredScript::Storage::MemoryAttributes::str() const{
	return "";
}

bool StructuredScript::Storage::MemoryAttributes::parse(INode::Ptr attributes, INode::Ptr target, ListType &parsed){
	Query::Node::ListType list;
	Query::Node::split(",", attributes, list);

	for (auto attribute : list){
		INode::Ptr args;
		IMemoryAttribute::Ptr resolved;
		std::string name;

		auto operatorNode = dynamic_cast<IOperatorNode *>(attribute.get());
		if (operatorNode != nullptr){//Attribute with argument?
			auto value = operatorNode->value();
			if (value == "()"){//Arguments
				auto binary = dynamic_cast<IBinaryOperatorNode *>(operatorNode);
				if (binary != nullptr){
					resolved = resolve(binary->leftOperand(), name);
					args = binary->rightOperand();
				}
				else//Unary -- no args
					resolved = resolve(dynamic_cast<IUnaryOperatorNode *>(operatorNode)->operand(), name);
			}
			else if (value == "::")//Scoped
				resolved = resolve(attribute, name);
			else
				return false;
		}
		else
			resolved = resolve(attribute, name);

		if (resolved == nullptr)
			return false;

		auto spawn = resolved->spawn(args, nullptr, nullptr, nullptr);
		if (spawn != nullptr && spawn->appliesTo(target, nullptr, nullptr, nullptr))
			parsed[name] = spawn;
		else
			return false;
	}

	return true;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Storage::MemoryAttributes::resolve(INode::Ptr target, std::string &name){
	name = target->str();

	auto operatorNode = dynamic_cast<IOperatorNode *>(target.get());
	if (operatorNode == nullptr){
		auto id = dynamic_cast<IIdentifierNode *>(target.get());
		return (id == nullptr) ? nullptr : dynamic_cast<IStorage *>(IGlobalStorage::globalStorage)->findMemoryAttribute(id->value());
	}

	if (operatorNode->value() != "::")
		return nullptr;

	auto binary = dynamic_cast<IBinaryOperatorNode *>(operatorNode);
	if (binary == nullptr)
		return nullptr;

	auto id = dynamic_cast<IIdentifierNode *>(binary->rightOperand().get());
	if (id == nullptr)
		return nullptr;

	std::string leftName;
	auto scope = resolve(binary->leftOperand(), leftName);

	return (scope == nullptr) ? nullptr : scope->find(id->value(), nullptr, nullptr, nullptr);
}
