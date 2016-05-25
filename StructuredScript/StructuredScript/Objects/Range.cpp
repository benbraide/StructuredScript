#include "Range.h"

StructuredScript::Objects::RangeBase::RangeBase()
	: Primitive(class_), Objects::PrimitiveObject(class_, Primitive::memory_){
	firstNode_->evaluate(this, nullptr, nullptr);
	secondNode_->evaluate(this, nullptr, nullptr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::RangeBase::ptr(){
	return shared_from_this();
}

void StructuredScript::Objects::RangeBase::init(){
	std::string lines = "class @range{";

	lines += "@[Call(0)]bool ascending();";
	lines += "@[Call(1)]bool descending()}";

	auto parsed = IGlobalStorage::globalStorage->parse(lines);

	class_ = dynamic_cast<IClassNode *>(parsed.get())->create(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), nullptr, nullptr);
	firstNode_ = IGlobalStorage::globalStorage->parse("any first{ @[Call(2)]unsigned int get(); @[Call(3)]void set(integral_type value) }");
	secondNode_ = IGlobalStorage::globalStorage->parse("any second{ @[Call(4)]unsigned int get(); @[Call(5)]void set(integral_type value) }");

	auto type = dynamic_cast<Type *>(class_.get());

	type->addExternalCall("0", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//call
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<RangeBase *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(object->ascending_());
	});

	type->addExternalCall("1", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//call_right
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<RangeBase *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(object->descending_());
	});

	type->addExternalCall("2", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<RangeBase *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return object->first_();
	});

	type->addExternalCall("3", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<RangeBase *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto value = storage->findMemory("value")->object()->base();
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		object->first_(value);
		return PrimitiveFactory::createVoid();
	});

	type->addExternalCall("4", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<RangeBase *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return object->second_();
	});

	type->addExternalCall("5", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<RangeBase *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto value = storage->findMemory("value")->object()->base();
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		object->second_(value);
		return PrimitiveFactory::createVoid();
	});
}

StructuredScript::IType::Ptr StructuredScript::Objects::RangeBase::class_;

StructuredScript::INode::Ptr StructuredScript::Objects::RangeBase::firstNode_;

StructuredScript::INode::Ptr StructuredScript::Objects::RangeBase::secondNode_;
