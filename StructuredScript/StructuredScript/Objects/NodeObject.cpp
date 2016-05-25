#include "NodeObject.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::NodeObject::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::NodeObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<NodeObject>(value_->clone(), Primitive::type_);
}

StructuredScript::INode::Ptr StructuredScript::Objects::NodeObject::value(){
	return value_;
}

void StructuredScript::Objects::NodeObject::init(){
	std::string lines = "class @node_type{";

	lines += "@[Call(0)]any evaluate(@[AssumeConstness]ref val any storage = current_storage);";
	lines += "@[Call(1)]any str()}";

	auto parsed = IGlobalStorage::globalStorage->parse(lines);
	class_ = dynamic_cast<IClassNode *>(parsed.get())->create(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), nullptr, nullptr);

	auto type = dynamic_cast<Type *>(class_.get());

	type->addExternalCall("0", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//evaluate
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<NodeObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto targetStorage = storage->findMemory("storage")->object()->base();
		storage = dynamic_cast<IStorageObject *>(targetStorage.get())->value();
		if (storage == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Target storage is invalid!", expr)));
		}

		return object->value_->evaluate(storage, exception, nullptr);
	});

	type->addExternalCall("1", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//str
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<NodeObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createString(object->value_->str());
	});
}

StructuredScript::IType::Ptr StructuredScript::Objects::NodeObject::class_;
