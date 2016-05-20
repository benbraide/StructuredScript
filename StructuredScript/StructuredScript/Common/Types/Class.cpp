#include "Class.h"

StructuredScript::IAny::Ptr StructuredScript::Class::create(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto object = std::make_shared<Objects::Object>(shared_from_this());
	for (auto field : fields_){//Allocate memories for fields
		auto declaration = dynamic_cast<IDeclarationNode *>(field.get());
		if (declaration == nullptr){
			if (!Query::Node::isProperty(field)){
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + field->str() + "': Expected a declaration!", expr)));
			}
			
			field->evaluate(object.get(), exception, expr);
			if (Query::ExceptionManager::has(exception))
				return nullptr;
		}

		if (!Query::Node::isInitialization(field)){//Allocate
			auto memory = declaration->allocate(object.get(), exception, expr);
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			if (memory->object() != nullptr){
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + field->str() + "': Expansions are only allowed as function parameters!", expr)));
			}

			dynamic_cast<IMemoryBackdoor *>(memory.get())->assign(PrimitiveFactory::createUndefined());
		}
		else{//Define
			field->evaluate(object.get(), exception, expr);
			if (Query::ExceptionManager::has(exception))
				return nullptr;
		}
	}

	for (auto parent : parents_){//Create base objects
		auto classParent = dynamic_cast<Class *>(parent.get());
		auto base = classParent->create(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		object->addParent(classParent->name_, std::make_shared<StructuredScript::Storage::Memory>(storage, parent, base, nullptr));
	}

	return object;
}

StructuredScript::IMemory::Ptr StructuredScript::Class::constructor(){
	return findFunctionMemory(name_, SEARCH_LOCAL);
}

StructuredScript::IMemory::Ptr StructuredScript::Class::destructor(){
	return findFunctionMemory("~" + name_, SEARCH_LOCAL);
}

void StructuredScript::Class::setFieldList(const FieldListType &fields){
	fields_ = fields;
}
