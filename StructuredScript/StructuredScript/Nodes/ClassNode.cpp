#include "ClassNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ClassNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::ClassNode::clone(){
	if (parents_ == nullptr)
		return std::make_shared<ClassNode>(name_->clone(), nullptr, value_->clone());

	return std::make_shared<ClassNode>(name_->clone(), parents_->clone(), value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::ClassNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = create(storage, exception, expr);
	return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createTypeObject(type);
}

std::string StructuredScript::Nodes::ClassNode::str(){
	if (parents_ == nullptr)
		return ("class " + name_->str() + "{...}");

	auto name = name_->str();
	if (name.empty())
		return ("class : " + parents_->str() + "{...}");

	return ("class " + name + " : " + parents_->str() + "{...}");
}

void StructuredScript::Nodes::ClassNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::ClassNode::attributes(){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Nodes::ClassNode::create(IStorage *storage, IExceptionManager *exception, INode *expr){
	std::string name;
	if (!Query::Node::isEmpty(name_)){//Named
		auto id = dynamic_cast<IIdentifierNode *>(name_.get());
		if (id == nullptr || Query::Node::isOperatorIdentifier(name_) || Query::Node::isTypeIdentifier(name_)){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + name_->str() + "': Expected an identifier!", expr)));

			return nullptr;
		}

		name = id->value();
	}

	Class::ParentListType parents;
	getParents_(parents, storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	Query::Node::ListType lines;
	Query::Node::split(";", value_, lines);

	Class::FieldListType fields;
	auto classType = std::make_shared<Class>(storage, parents, name);

	if (!name.empty()){//Add named class to storage
		auto added = storage->addType(name);
		if (added == nullptr){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Failed to create class!", expr)));

			return nullptr;
		}

		*added = classType;
	}

	for (auto line : lines){//Evaluate | Add to field list
		if (Query::Node::isProperty(line)){//Check for static declarations
			auto property = dynamic_cast<IPropertyNode *>(line.get());
			if (isStatic_(dynamic_cast<IDeclarationNode *>(property->declaration().get())))//Add static property to class
				line->evaluate(classType.get(), exception, expr);
			else//Add to list
				fields.push_back(line);
		}
		else if (Query::Node::isDeclaration(line)){//Check for static declarations
			if (isStatic_(dynamic_cast<IDeclarationNode *>(line.get())))//Add static field to class
				line->evaluate(classType.get(), exception, expr);
			else//Add to list
				fields.push_back(line);
		}
		else//Add to class
			line->evaluate(classType.get(), exception, expr);

		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	classType->setFieldList(fields);
	return classType;
}

void StructuredScript::Nodes::ClassNode::value(INode::Ptr value){
	value_ = value;
}

StructuredScript::INode::Ptr StructuredScript::Nodes::ClassNode::value(){
	return value_;
}

std::string StructuredScript::Nodes::ClassNode::declName(){
	return name_->str();
}

void StructuredScript::Nodes::ClassNode::getParents_(Class::ParentListType &parents, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (parents_ == nullptr)
		return;

	Query::Node::ListType list;
	Query::Node::split(",", parents_, list);

	for (auto parent : list){
		auto resolver = dynamic_cast<ITypeResolver *>(parent.get());
		auto type = (resolver == nullptr) ? nullptr : resolver->resolveType(storage);
		if (type == nullptr){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + parent->str() + "': Could not resolve type!", expr)));

			return;
		}

		parents.push_back(type);
	}
}

bool StructuredScript::Nodes::ClassNode::isStatic_(IDeclarationNode *declaration){
	auto type = declaration->type();
	auto declType = dynamic_cast<IModifiedTypeIdentifierNode *>(type.get());

	return (declType == nullptr) ? false : StructuredScript::Storage::MemoryState(declType->states()).isStatic();
}
