#include "BlockPairNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::BlockPairNode::clone(){
	return std::make_shared<BlockPairNode>(leftOperand_, rightOperand_);
}

std::string StructuredScript::Nodes::BlockPairNode::str(){
	return (leftOperand_->str() + "\n" + rightOperand_->str());
}
