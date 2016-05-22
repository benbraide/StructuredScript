#include "FunctionObject.h"

StructuredScript::Objects::FunctionObject::FunctionObject(IMemory::Ptr value)
	: Primitive(class_), Objects::PrimitiveObject(class_, Primitive::memory_), value_(value){
	lengthNode_->evaluate(this, nullptr, nullptr);

	if (dynamic_cast<IFunctionMemory *>(value_.get()) != nullptr){
		auto object = dynamic_cast<IAny *>(value_->storage());
		if (object != nullptr)
			bound_ = object->ptr();
	}
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::FunctionObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<FunctionObject>(value_);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::FunctionObject::base(){
	return shared_from_this();
}

std::string StructuredScript::Objects::FunctionObject::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot get string value of object!", expr)));

	return "";
}

void StructuredScript::Objects::FunctionObject::init(){
	std::string lines = "class @function_type{";

	lines += "@[Call(0)]any call(@[AssumeConstness]ref val any... args);";
	lines += "@[Call(1)]any call_right();";
	lines += "@[Call(2)]function_type find(@[AssumeConstness]ref val any... args);";
	lines += "@[Call(3)]function_type find_right();";
	lines += "@[Call(4)]function_type first();";
	lines += "@[Call(5)]function_type filter();";
	lines += "@[Call(6)]function_type bind(@[AssumeConstness]ref val any object);";
	lines += "@[Call(7)]bool is_bound();";
	lines += "@[Call(8)]bool is_collection()}";

	auto parsed = IGlobalStorage::globalStorage->parse(lines);

	class_ = dynamic_cast<IClassNode *>(parsed.get())->create(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), nullptr, nullptr);
	lengthNode_ = IGlobalStorage::globalStorage->parse("any length{ @[Call(9)]unsigned int get() }");

	auto type = dynamic_cast<Type *>(class_.get());

	type->addExternalCall("0", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//call
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		IFunction::ArgListType args;
		auto target = storage->findMemory("args")->object();
		dynamic_cast<IExpansion *>(target.get())->expand(args);

		auto functionMemory = dynamic_cast<IFunctionMemory *>(object->value_.get());
		if (functionMemory != nullptr)
			return functionMemory->call(false, args, exception, expr);

		auto function = (object->value_ == nullptr) ? nullptr : dynamic_cast<IFunction *>(object->value_->object().get());
		if (function == nullptr || function->score(false, object->bound_, args) < 1){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("No function found taking the specified arguments!", expr)));
		}

		return function->call(false, object->bound_, args, exception, expr);
	});

	type->addExternalCall("1", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//call_right
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto functionMemory = dynamic_cast<IFunctionMemory *>(object->value_.get());
		if (functionMemory != nullptr)
			return functionMemory->call(true, {}, exception, expr);

		auto function = (object->value_ == nullptr) ? nullptr : dynamic_cast<IFunction *>(object->value_->object().get());
		if (function == nullptr || function->score(true, object->bound_, IFunction::ArgListType{}) < 1){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("No function found taking the specified arguments!", expr)));
		}

		return function->call(true, object->bound_, {}, exception, expr);
	});

	type->addExternalCall("2", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		IFunction::ArgListType args;
		auto target = storage->findMemory("args")->object();
		dynamic_cast<IExpansion *>(target.get())->expand(args);

		auto functionMemory = dynamic_cast<IFunctionMemory *>(object->value_.get());
		if (functionMemory != nullptr)
			return std::make_shared<FunctionObject>(functionMemory->find(false, args));

		auto function = (object->value_ == nullptr) ? nullptr : dynamic_cast<IFunction *>(object->value_->object().get());
		if (function == nullptr || function->score(false, object->bound_, args) < 1)
			return std::make_shared<FunctionObject>(nullptr);

		return std::make_shared<FunctionObject>(object->value_);
	});

	type->addExternalCall("3", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//find_right
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto functionMemory = dynamic_cast<IFunctionMemory *>(object->value_.get());
		if (functionMemory != nullptr)
			return std::make_shared<FunctionObject>(functionMemory->find(true, IFunction::ArgListType{}));

		auto function = (object->value_ == nullptr) ? nullptr : dynamic_cast<IFunction *>(object->value_->object().get());
		if (function == nullptr || function->score(true, object->bound_, IFunction::ArgListType{}) < 1)
			return std::make_shared<FunctionObject>(nullptr);

		return std::make_shared<FunctionObject>(object->value_);
	});

	type->addExternalCall("4", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//first
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto functionMemory = dynamic_cast<IFunctionMemory *>(object->value_.get());
		if (functionMemory == nullptr)
			return std::make_shared<FunctionObject>(nullptr);

		return std::make_shared<FunctionObject>(functionMemory->first());
	});

	type->addExternalCall("5", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//filter
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		if (object->value_ == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot filter an empty function list!", expr)));
		}

		auto functionMemory = dynamic_cast<IFunctionMemory *>(object->value_.get());
		if (functionMemory == nullptr)
			return std::make_shared<FunctionObject>(nullptr);

		return std::make_shared<FunctionObject>(functionMemory->filterNonMembers());
	});

	type->addExternalCall("6", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//bind
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		if (object->value_ == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot bind to an empty function list!", expr)));
		}

		auto target = storage->findMemory("object")->object()->base();
		auto objectStorage = dynamic_cast<IStorage *>(target.get());
		if (objectStorage == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Target is not an object!", expr)));
		}

		if (dynamic_cast<IFunctionMemory *>(object->value_.get()) == nullptr){
			auto memory = std::make_shared<StructuredScript::Storage::FunctionMemory>(ListType{ object->value_ }, objectStorage);
			return std::make_shared<FunctionObject>(memory);
		}

		auto memory = object->value_->clone();
		dynamic_cast<IFunctionMemory *>(memory.get())->setStorage(objectStorage);

		return std::make_shared<FunctionObject>(memory);
	});

	type->addExternalCall("7", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//is_bound
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(object->bound_ != nullptr);
	});

	type->addExternalCall("8", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//is_collection
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(dynamic_cast<IFunctionMemory *>(object->value_.get()) != nullptr);
	});

	type->addExternalCall("9", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//length.get
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<FunctionObject *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto functionMemory = dynamic_cast<IFunctionMemory *>(object->value_.get());
		if (functionMemory != nullptr)
			return PrimitiveFactory::createUInt(functionMemory->count());

		return PrimitiveFactory::createUInt((object->value_ == nullptr) ? 0 : 1);
	});
}

StructuredScript::IType::Ptr StructuredScript::Objects::FunctionObject::class_;

StructuredScript::INode::Ptr StructuredScript::Objects::FunctionObject::lengthNode_;
