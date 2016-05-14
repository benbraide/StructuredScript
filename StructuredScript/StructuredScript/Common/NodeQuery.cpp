#include "NodeQuery.h"

bool StructuredScript::Query::Node::isEmpty(INode::Ptr node){
	return (dynamic_cast<IEmptyNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isIdentifier(INode::Ptr node){
	return (dynamic_cast<IIdentifierNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isIdentifierExpression(INode::Ptr node){
	if (dynamic_cast<IIdentifierExpressionNode *>(node.get()) != nullptr)
		return true;

	auto operatorNode = dynamic_cast<IOperatorNode *>(node.get());
	if (operatorNode != nullptr && (operatorNode->value() == "." || operatorNode->value() == "::"))
		return true;

	return false;
}

bool StructuredScript::Query::Node::isOperatorIdentifier(INode::Ptr node){
	return (dynamic_cast<IOperatorIdentifierNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isTypeIdentifier(INode::Ptr node){
	return (dynamic_cast<ITypeIdentifierNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isExpandedTypeIdentifier(INode::Ptr node){
	return (dynamic_cast<IExpandedTypenameIdentifierNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isDeclaration(INode::Ptr node){
	return (dynamic_cast<IDeclarationNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isInitialization(INode::Ptr node){
	return false;
}

bool StructuredScript::Query::Node::isParameter(INode::Ptr node){
	return false;
}

bool StructuredScript::Query::Node::isMember(INode::Ptr node){
	return false;
}

bool StructuredScript::Query::Node::isControl(INode::Ptr node){
	return false;
}

bool StructuredScript::Query::Node::isFunction(INode::Ptr node){
	return (dynamic_cast<IFunctionDeclarationNode *>(node.get()) != nullptr || dynamic_cast<IFunctionDefinitionNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isFunctionDeclaration(INode::Ptr node){
	return dynamic_cast<IFunctionDeclarationNode *>(node.get()) != nullptr;
}

bool StructuredScript::Query::Node::isFunctionDefinition(INode::Ptr node){
	return dynamic_cast<IFunctionDefinitionNode *>(node.get()) != nullptr;
}

bool StructuredScript::Query::Node::isLoop(INode::Ptr node){
	return false;
}

bool StructuredScript::Query::Node::isSelection(INode::Ptr node){
	return false;
}

bool StructuredScript::Query::Node::isBlock(INode::Ptr node){
	return (dynamic_cast<IBlockNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isPlainBlock(INode::Ptr node){
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
	else if (dynamic_cast<IEmptyNode *>(node.get()) == nullptr)//Not operator -- add non-empty node
		list.push_back(node);
}

StructuredScript::IStorage *StructuredScript::Query::Node::resolveAsStorage(INode::Ptr node, IStorage *storage){
	auto resolver = dynamic_cast<IStorageResolver *>(node.get());
	if (resolver != nullptr)
		return resolver->resolveStorage(storage);

	bool localOnly;
	std::string value;
	
	if (!resolvePartial_(node, storage, value, localOnly))
		return nullptr;

	return storage->findStorage(value, localOnly);
}

StructuredScript::IType::Ptr StructuredScript::Query::Node::resolveAsType(INode::Ptr node, IStorage *storage){
	auto resolver = dynamic_cast<ITypeResolver *>(node.get());
	if (resolver != nullptr)
		return resolver->resolveType(storage);

	bool localOnly;
	std::string value;

	if (!resolvePartial_(node, storage, value, localOnly))
		return nullptr;

	return storage->findType(value, localOnly);
}

StructuredScript::IMemory::Ptr StructuredScript::Query::Node::resolveAsObject(INode::Ptr node, IStorage *storage){
	auto resolver = dynamic_cast<IMemoryResolver *>(node.get());
	if (resolver != nullptr)
		return resolver->resolveMemory(storage);

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
