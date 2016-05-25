#include "StorageObject.h"

StructuredScript::Objects::StorageObject::StorageObject(IStorage *value)
	: Primitive(class_), Objects::PrimitiveObject(class_, Primitive::memory_), value_(value){
	parentNode_->evaluate(this, nullptr, nullptr);
	validNode_->evaluate(this, nullptr, nullptr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::StorageObject::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::StorageObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<StorageObject>(value_);
}

StructuredScript::IStorage *StructuredScript::Objects::StorageObject::value(){
	return value_;
}

void StructuredScript::Objects::StorageObject::init(){
	std::string lines = "class @storage_type{";

	lines += "@[Call(0)]any find_storage(const ref val string name, unsigned short search_scope = SEARCH_DEFAULT);";
	lines += "@[Call(1)]any find_type(const ref val string name, unsigned short search_scope = SEARCH_DEFAULT);";
	lines += "@[Call(2)]any find_memory(const ref val string name, unsigned short search_scope = SEARCH_DEFAULT);";
	lines += "@[Call(3)]any find_function(const ref val string name, unsigned short search_scope = SEARCH_DEFAULT);";
	lines += "@[Call(4)]any find_operator(const ref val string name, unsigned short search_scope = SEARCH_DEFAULT);";
	lines += "@[Call(5)]any find_type_operator(const ref val type name, unsigned short search_scope = SEARCH_DEFAULT);";
	lines += "@[Call(6)]bool operator bool();";

	lines += "static const unsigned short SEARCH_DEFAULT = 0x0000;";
	lines += "static const unsigned short SEARCH_FAMILY = 0x0001;";
	lines += "static const unsigned short SEARCH_LOCAL = 0x0002}";

	auto parsed = IGlobalStorage::globalStorage->parse(lines);

	class_ = dynamic_cast<IClassNode *>(parsed.get())->create(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), nullptr, nullptr);
	parentNode_ = IGlobalStorage::globalStorage->parse("any parent{ @[Call(7)]storage_type get() }");
	validNode_ = IGlobalStorage::globalStorage->parse("any valid{ @[Call(8)]bool get() }");

	auto type = dynamic_cast<Type *>(class_.get());

	type->addExternalCall("0", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find_storage
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto name = storage->findMemory("name")->object()->base();
		if (name == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		auto searchScope = static_cast<unsigned short>(Query::Object::getIndex(storage->findMemory("search_scope")->object()));
		return std::make_shared<StorageObject>(object->value_->findStorage(name->str(storage, exception, expr), searchScope));
	});

	type->addExternalCall("1", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find_type
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto name = storage->findMemory("name")->object()->base();
		if (name == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		auto searchScope = static_cast<unsigned short>(Query::Object::getIndex(storage->findMemory("search_scope")->object()));
		return PrimitiveFactory::createTypeObject(object->value_->findType(name->str(storage, exception, expr), searchScope));
	});

	type->addExternalCall("2", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find_memory
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto name = storage->findMemory("name")->object()->base();
		if (name == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		auto searchScope = static_cast<unsigned short>(Query::Object::getIndex(storage->findMemory("search_scope")->object()));
		auto memory = object->value_->findMemory(name->str(storage, exception, expr), searchScope);

		if (dynamic_cast<IFunctionMemory *>(memory.get()) == nullptr)
			return PrimitiveFactory::createMemoryObject(memory);

		return PrimitiveFactory::createFunctionObject(memory);
	});

	type->addExternalCall("3", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find_function
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto name = storage->findMemory("name")->object()->base();
		if (name == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		auto searchScope = static_cast<unsigned short>(Query::Object::getIndex(storage->findMemory("search_scope")->object()));
		return PrimitiveFactory::createFunctionObject(object->value_->findFunctionMemory(name->str(storage, exception, expr), searchScope));
	});

	type->addExternalCall("4", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find_operator
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto name = storage->findMemory("name")->object()->base();
		if (name == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		auto searchScope = static_cast<unsigned short>(Query::Object::getIndex(storage->findMemory("search_scope")->object()));
		return PrimitiveFactory::createFunctionObject(object->value_->findOperatorMemory(name->str(storage, exception, expr), searchScope));
	});

	type->addExternalCall("5", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find_type_operator
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto name = storage->findMemory("name")->object()->base();
		if (name == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		auto type = dynamic_cast<ITypeObject *>(name.get())->value();
		if (type == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Target type is invalid!", expr)));
		}

		auto searchScope = static_cast<unsigned short>(Query::Object::getIndex(storage->findMemory("search_scope")->object()));
		return PrimitiveFactory::createFunctionObject(object->value_->findTypenameOperatorMemory(type, searchScope));
	});

	type->addExternalCall("6", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//operator bool
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(object->value_ != nullptr);
	});

	type->addExternalCall("7", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//parent.get
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		if (object->value_ == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Storage is invalid!", expr)));
		}

		return std::make_shared<StorageObject>(object->value_->parent());
	});

	type->addExternalCall("8", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//valid.get
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<StorageObject *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(object->value_ != nullptr);
	});
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::StorageObject::evaluate_(const std::string &value, bool reversed, Ptr right,
	IExceptionManager *exception, INode *expr){
	auto rightBase = right->base();
	auto alike = dynamic_cast<StorageObject *>(rightBase.get());
	if (alike != nullptr){
		if (value == "==" || value == "<=" || value == ">=")
			return PrimitiveFactory::createBool(value_ == alike->value_);

		if (value == "!=")
			return PrimitiveFactory::createBool(value_ != alike->value_);
	}

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

StructuredScript::IType::Ptr StructuredScript::Objects::StorageObject::class_;

StructuredScript::INode::Ptr StructuredScript::Objects::StorageObject::parentNode_;

StructuredScript::INode::Ptr StructuredScript::Objects::StorageObject::validNode_;
