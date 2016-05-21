#include "LambdaNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::LambdaNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::LambdaNode::clone(){
	auto parametersClone = (parameters_ == nullptr) ? nullptr : parameters_->clone();
	auto typeClone = (type_ == nullptr) ? nullptr : type_->clone();

	return std::make_shared<LambdaNode>(captures_->clone(), parametersClone, typeClone, value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::LambdaNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	std::string parameters, initializers, fields, values;

	Query::Node::ListType captures;
	Query::Node::split(",", captures_, captures);

	auto self = false;
	for (auto capture : captures){
		auto isSelf = parseCapture_("", capture, parameters, initializers, fields, values, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		if (isSelf){
			if (self){
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'self': Multiple instances found in lambda capture list!", expr)));
			}
			
			self = true;
		}
	}

	std::string transformed = "class{__constructor(" + parameters + ")";
	if (!initializers.empty())
		transformed += ":" + initializers + "{}";
	else
		transformed += "{}";

	transformed += fields + "}";
	auto transformedNode = IGlobalStorage::globalStorage->parse(transformed);
	if (transformedNode == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Failed to define lambda!", expr)));
	}

	auto classNode = dynamic_cast<IClassNode *>(transformedNode.get());
	if (classNode == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Failed to define lambda!", expr)));
	}

	auto parametersStr = (parameters_ == nullptr) ? "" : parameters_->str();
	auto typeStr = (type_ == nullptr) ? "any" : type_->str();

	auto declaration = IGlobalStorage::globalStorage->parse(typeStr + " operator()");
	if (declaration == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Failed to define lambda!", expr)));
	}

	auto parametersNode = (parameters_ == nullptr) ? std::make_shared<EmptyNode>() : parameters_;
	auto function = std::make_shared<FunctionDefinitionNode>(declaration, parametersNode, value_);

	classNode->value(std::make_shared<BlockPairNode>(classNode->value(), function));//Insert operator function

	if (!values.empty()){//Add arguments
		auto args = IGlobalStorage::globalStorage->parse(values);
		if (args == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Failed to define lambda!", expr)));
		}

		transformedNode = std::make_shared<BinaryOperatorNode>("()", transformedNode, args);
	}

	auto object = std::make_shared<NewNode>(transformedNode)->evaluate(storage, exception, expr);//Create new unnamed instance
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (self){
		auto target = dynamic_cast<Objects::Any *>(Query::Object::getObjectInStorage(storage));
		if (target == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'self': Found in lambda capture list outside of object!", expr)));
		}

		dynamic_cast<Objects::Object *>(object.get())->self(target);
	}

	return object;
}

std::string StructuredScript::Nodes::LambdaNode::str(){
	auto typeStr = (type_ == nullptr) ? nullptr : type_->str();
	if (parameters_ == nullptr){
		if (typeStr.empty())
			return ("[" + captures_->str() + "]{...}");

		return ("[" + captures_->str() + "] -> " + typeStr + "{...}");
	}

	if (typeStr.empty())
		return ("[" + captures_->str() + "](" + parameters_->str() + "){...}");

	return ("[" + captures_->str() + "](" + parameters_->str() + ") -> " + typeStr + "{...}");
}

void StructuredScript::Nodes::LambdaNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::LambdaNode::attributes(){
	return nullptr;
}

bool StructuredScript::Nodes::LambdaNode::parseCapture_(const std::string &prefix, Ptr capture, std::string &parameters, std::string &initializers,
	std::string &fields, std::string &values, IExceptionManager *exception, INode *expr){
	auto unary = dynamic_cast<IUnaryOperatorNode *>(Query::Node::getBase(capture).get());
	if (unary != nullptr){// &capture
		if (!prefix.empty()){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + prefix + capture->str() + "': Bad lambda capture!", expr)));

			return false;
		}

		if (unary->value() != "&"){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + capture->str() + "': Bad lambda capture!", expr)));

			return false;
		}

		return parseCapture_("ref", unary->operand(), parameters, initializers, fields, values, exception, expr);
	}
	
	auto captureStr = capture->str();
	if (captureStr == "self"){
		if (!prefix.empty()){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + prefix + capture->str() + "': Bad lambda capture!", expr)));

			return false;
		}

		return true;
	}

	if (!Query::Node::isIdentifier(capture) || Query::Node::isOperatorIdentifier(capture) || Query::Node::isTypeIdentifier(capture)){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + captureStr + "': Bad lambda capture!", expr)));
	}
	else
		append_(prefix, captureStr, parameters, initializers, fields, values);

	return false;
}

void StructuredScript::Nodes::LambdaNode::append_(const std::string &prefix, const std::string &captureStr, std::string &parameters,
	std::string &initializers, std::string &fields, std::string &values){
	if (parameters.empty())
		parameters = "ref any " + captureStr;
	else
		parameters += ", ref any " + captureStr;

	if (initializers.empty())
		initializers = captureStr + "(" + captureStr + ")";
	else
		initializers += ", " + captureStr + "(" + captureStr + ")";

	if (fields.empty())
		fields = prefix + " any " + captureStr;
	else
		fields += "; " + prefix + " any " + captureStr;

	if (values.empty())
		values = captureStr;
	else
		values += ", " + captureStr;
}
