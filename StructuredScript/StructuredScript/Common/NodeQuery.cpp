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
	return (dynamic_cast<IInitializationNode *>(node.get()) != nullptr);
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

bool StructuredScript::Query::Node::isGroup(INode::Ptr node){
	return (dynamic_cast<IGroupNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isIndex(INode::Ptr node){
	return (dynamic_cast<IIndexNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isBlock(INode::Ptr node){
	return (dynamic_cast<IBlockNode *>(node.get()) != nullptr);
}

bool StructuredScript::Query::Node::isPlainBlock(INode::Ptr node){
	return false;
}

StructuredScript::INode::Ptr StructuredScript::Query::Node::getBaseId(INode::Ptr node){
	auto operatorNode = dynamic_cast<IOperatorNode *>(node.get());
	if (operatorNode == nullptr || operatorNode->value() != "::")
		return node;

	auto unary = dynamic_cast<IUnaryOperatorNode *>(operatorNode);
	return (unary == nullptr) ? dynamic_cast<IBinaryOperatorNode *>(operatorNode)->rightOperand() : unary->operand();
}

void StructuredScript::Query::Node::split(const std::string &value, INode::Ptr node, ListType &list, bool forceBinary /*= false*/){
	if (node == nullptr)
		return;

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

StructuredScript::IStorage *StructuredScript::Query::Node::resolveAsStorage(INode::Ptr node, IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto resolver = dynamic_cast<IStorageResolver *>(node.get());
	return (resolver == nullptr) ? nullptr : resolver->resolveStorage(storage, searchScope);
}

StructuredScript::IType::Ptr StructuredScript::Query::Node::resolveAsType(INode::Ptr node, IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto resolver = dynamic_cast<ITypeResolver *>(node.get());
	return (resolver == nullptr) ? nullptr : resolver->resolveType(storage, searchScope);
}

StructuredScript::IMemory::Ptr StructuredScript::Query::Node::resolveAsMemory(INode::Ptr node, IStorage *storage, unsigned short searchScope /*= IStorage::SEARCH_DEFAULT*/){
	auto resolver = dynamic_cast<IMemoryResolver *>(node.get());
	return (resolver == nullptr) ? nullptr : resolver->resolveMemory(storage, searchScope);
}
