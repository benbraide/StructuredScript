#include "NodeQuery.h"

bool StructuredScript::Query::Node::isEmpty(const INode *node){
	return (dynamic_cast<const IEmptyNode *>(node) != nullptr);
}

bool StructuredScript::Query::Node::isDeclaration(const INode *node){
	return false;
}

bool StructuredScript::Query::Node::isAssignment(const INode *node){
	return false;
}

bool StructuredScript::Query::Node::isParameter(const INode *node){
	return false;
}

bool StructuredScript::Query::Node::isMember(const INode *node){
	return false;
}

bool StructuredScript::Query::Node::isControl(const INode *node){
	return false;
}

bool StructuredScript::Query::Node::isLoop(const INode *node){
	return false;
}

bool StructuredScript::Query::Node::isSelection(const INode *node){
	return false;
}

bool StructuredScript::Query::Node::isBlock(const INode *node){
	return (dynamic_cast<const IBlockNode *>(node) != nullptr);
}

bool StructuredScript::Query::Node::isPlainBlock(const INode *node){
	return false;
}

void StructuredScript::Query::Node::split(const std::string &value, INode::Ptr node, ListType &list, bool forceBinary /*= false*/){
	auto operatorNode = dynamic_cast<IOperatorNode *>(node.get());
	if (operatorNode != nullptr){//Operator
		if (operatorNode->value() == value){//Values match -- split
			auto unaryOperator = dynamic_cast<IUnaryOperatorNode *>(node.get());
			if (unaryOperator == nullptr){//Try binary
				auto binaryOperator = dynamic_cast<IBinaryOperatorNode *>(node.get());
				if (binaryOperator != nullptr){//Binary
					split(value, binaryOperator->leftOperand(), list, forceBinary);
					split(value, binaryOperator->rightOperand(), list, forceBinary);
				}
				else//Unknown -- don't split
					list.push_back(node);
			}
			else{//Unary
				split(value, unaryOperator->operand(), list, forceBinary);
				if (forceBinary)
					list.push_back(nullptr);
			}
		}
		else//Operator mismatch -- don't split
			list.push_back(node);
	}
	else if (/*dynamic_cast<IEmptyNode *>(node.get()) != nullptr*/true)//Not operator -- add non-empty node
		list.push_back(node);
}

StructuredScript::IStorage *StructuredScript::Query::Node::resolveAsStorage(INode::Ptr node, IStorage *storage){
	bool localOnly;
	std::string value;
	
	if (!resolvePartial_(node, storage, value, localOnly))
		return nullptr;

	return storage->findStorage(value, localOnly);
}

StructuredScript::IType::Ptr StructuredScript::Query::Node::resolveAsType(INode::Ptr node, IStorage *storage){
	bool localOnly;
	std::string value;

	if (!resolvePartial_(node, storage, value, localOnly))
		return nullptr;

	return storage->findType(value, localOnly);
}

StructuredScript::IMemory::Ptr StructuredScript::Query::Node::resolveAsObject(INode::Ptr node, IStorage *storage){
	bool localOnly;
	std::string value;

	if (!resolvePartial_(node, storage, value, localOnly))
		return nullptr;

	return storage->findMemory(value, localOnly);
}

bool StructuredScript::Query::Node::resolvePartial_(INode::Ptr node, IStorage *&storage, std::string &value, bool &localOnly){
	if (storage == nullptr)
		return false;

	auto operatorNode = dynamic_cast<IOperatorNode *>(node.get());
	if (operatorNode != nullptr){//Operator must be '::'
		if (operatorNode->value() != "::")
			return false;

		auto binary = dynamic_cast<IBinaryOperatorNode *>(node.get());
		if (binary == nullptr){//Unary
			auto unary = dynamic_cast<IUnaryOperatorNode *>(node.get());
			if (unary == nullptr)//Unknown
				return false;

			auto operand = unary->operand();
			auto id = dynamic_cast<IIdentifierNode *>(operand.get());
			if (id == nullptr)//Bad node
				return false;

			storage = dynamic_cast<IStorage *>(IGlobalStorage::globalStorage);
			value = id->value();
		}
		else{
			auto operand = binary->rightOperand();
			auto id = dynamic_cast<IIdentifierNode *>(operand.get());
			if (id == nullptr)//Bad node
				return false;

			storage = resolveAsStorage(binary->leftOperand(), storage);
			if (storage == nullptr)//Failed to resolve
				return false;

			value = id->value();
		}

		localOnly = true;
	}
	else{
		auto id = dynamic_cast<IIdentifierNode *>(node.get());
		if (id == nullptr)//Bad node
			return false;

		value = id->value();
		localOnly = false;
	}

	return true;
}
