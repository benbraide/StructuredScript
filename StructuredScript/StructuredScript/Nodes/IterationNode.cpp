#include "IterationNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::WhileNode::clone(){
	return std::make_shared<WhileNode>(predicate_->clone(), value_->clone());
}

std::string StructuredScript::Nodes::WhileNode::str(){
	return ("while (" + predicate_->str() + "){...}");
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::DoWhileNode::clone(){
	return std::make_shared<DoWhileNode>(predicate_->clone(), value_->clone());
}

std::string StructuredScript::Nodes::DoWhileNode::str(){
	return ("do{...}while (" + predicate_->str() + ")");
}

StructuredScript::Nodes::ForNode::ForNode(Ptr predicate, Ptr value)
	: IteratorNode(value){
	Query::Node::ListType list;
	Query::Node::split(";", predicate, list, true);

	if (list.size() == 3u){//for (int; pred; update){...}
		init_ = *list.begin();
		if (init_ == nullptr)
			init_ = std::make_shared<EmptyNode>();

		predicate_ = *std::next(list.begin());
		if (predicate_ == nullptr)
			predicate_ = std::make_shared<EmptyNode>();

		update_ = *list.rbegin();
		if (update_ == nullptr)
			update_ = std::make_shared<EmptyNode>();
	}
	else//for (variable : object){...}
		predicate_ = predicate;
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ForNode::clone(){
	if (init_ == nullptr || update_ == nullptr)
		return std::make_shared<ForNode>(nullptr, predicate_->clone(), nullptr, value_->clone());
	return std::make_shared<ForNode>(init_->clone(), predicate_->clone(), update_->clone(), value_->clone());
}

std::string StructuredScript::Nodes::ForNode::str(){
	return ("for (" + predicate_->str() + "){...}");
}

void StructuredScript::Nodes::ForNode::before_(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (init_ != nullptr && !Query::Node::isEmpty(init_))
		init_->evaluate(storage, exception, expr);
}

void StructuredScript::Nodes::ForNode::after_(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (update_ != nullptr && !Query::Node::isEmpty(update_))
		update_->evaluate(storage, exception, expr);
}
