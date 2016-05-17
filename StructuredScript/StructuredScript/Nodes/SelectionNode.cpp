#include "SelectionNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::IfNode::clone(){
	return std::make_shared<IfNode>(predicate_->clone(), value_->clone());
}

std::string StructuredScript::Nodes::IfNode::str(){
	return ("if (" + predicate_->str() + "){...}");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::UnlessNode::clone(){
	return std::make_shared<UnlessNode>(predicate_->clone(), value_->clone());
}

std::string StructuredScript::Nodes::UnlessNode::str(){
	return ("unless (" + predicate_->str() + "){...}");
}

bool StructuredScript::Nodes::UnlessNode::truth_(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (predicate_ == nullptr || Query::Node::isEmpty(predicate_))
		return false;

	auto value = predicate_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return false;

	auto truth = value->truth(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return false;

	return !truth;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ElseNode::clone(){
	return std::make_shared<ElseNode>(value_->clone());
}

std::string StructuredScript::Nodes::ElseNode::str(){
	return ("else{...}");
}

bool StructuredScript::Nodes::ElseNode::truth_(IStorage *storage, IExceptionManager *exception, INode *expr){
	return true;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ConditionalNode::clone(){
	return std::make_shared<ConditionalNode>(predicate_->clone(), value_->clone(), elseNode_->clone());
}

std::string StructuredScript::Nodes::ConditionalNode::str(){
	return (predicate_->str() + " ? " + value_->str() + " : " + elseNode_->str());
}
