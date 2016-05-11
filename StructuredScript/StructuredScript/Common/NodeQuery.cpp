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
