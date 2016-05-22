#include "Array.h"

StructuredScript::Objects::ArrayObject::ArrayObject()
	: Primitive(class_), Objects::PrimitiveObject(class_, Primitive::memory_){
	lengthNode_->evaluate(this, nullptr, nullptr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::ArrayObject::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto object = std::make_shared<ArrayObject>();
	for (auto entry : entries_){//Copy entries
		object->append(entry->object(), storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	return object;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::ArrayObject::evaluateRightUnary(const std::string &value, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	if (value != "[]")
		return Primitive::evaluateRightUnary(value, storage, exception, expr);

	return nullptr;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::ArrayObject::evaluateBinary(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	if (value != "[]")
		return Primitive::evaluateBinary(value, right, storage, exception, expr);

	auto rightBase = right->base();
	if (dynamic_cast<IInteger *>(rightBase.get()) == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'[]': Expected index to be an integral value!", expr)));
	}

	auto index = static_cast<int>(Query::Object::getIndex(rightBase));
	if (index < 0){

	}
	else if (static_cast<unsigned int>(index) >= entries_.size()){

	}

	return entries_[index]->object();
}

StructuredScript::IAny::Ptr StructuredScript::Objects::ArrayObject::at(unsigned int index){
	return (index < entries_.size()) ? entries_[index]->object() : nullptr;
}

void StructuredScript::Objects::ArrayObject::append(IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr){
	add_(entries_.end(), value->type())->assign(value, storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		entries_.pop_back();//Undo
}

void StructuredScript::Objects::ArrayObject::insert(unsigned int index, IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (index < entries_.size()){
		add_(entries_.begin() + index, value->type())->assign(value, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			entries_.erase(entries_.begin() + index);//Undo
	}
	else{
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Index is out of bounds!", expr)));
	}
}

void StructuredScript::Objects::ArrayObject::insert(MemoryListType::iterator index, IAny::Ptr value, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (index != entries_.end()){
		add_(index, value->type())->assign(value, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			entries_.erase(index);//Undo
	}
	else{
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Index is out of bounds!", expr)));
	}
}

void StructuredScript::Objects::ArrayObject::erase(unsigned int index){
	if (index < entries_.size())
		entries_.erase(entries_.begin() + index);
}

void StructuredScript::Objects::ArrayObject::erase(MemoryListType::iterator index){
	if (index != entries_.end())
		entries_.erase(index);
}

void StructuredScript::Objects::ArrayObject::clear(){
	entries_.clear();
}

bool StructuredScript::Objects::ArrayObject::empty(){
	return entries_.empty();
}

unsigned int StructuredScript::Objects::ArrayObject::size(){
	return entries_.size();
}

void StructuredScript::Objects::ArrayObject::size(unsigned int value){

}

void StructuredScript::Objects::ArrayObject::init(){
	std::string lines = "class @array{";

	lines += "@[Call(0), AssumeConstness]ref val any at(integral_type index);";
	lines += "@[Call(1)]void append(@[AssumeConstness] ref val any value);";
	lines += "@[Call(2)]void insert(integral_type index, @[AssumeConstness] ref val any value);";
	lines += "@[Call(3)]void erase(integral_type index);";
	lines += "@[Call(4)]void clear();";
	lines += "@[Call(5)]bool empty()}";

	auto parsed = IGlobalStorage::globalStorage->parse(lines);

	class_ = dynamic_cast<IClassNode *>(parsed.get())->create(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), nullptr, nullptr);
	lengthNode_ = IGlobalStorage::globalStorage->parse("any length{ @[Call(6)]unsigned int get(); @[Call(7)]void set(integral_type size) }");

	auto type = dynamic_cast<Type *>(class_.get());

	type->addExternalCall("0", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= object->entries_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		return object->at(index);
	});

	type->addExternalCall("1", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto value = storage->findMemory("value")->object()->base();
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		object->append(value, storage, exception, expr);
		return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createVoid();
	});

	type->addExternalCall("2", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto value = storage->findMemory("value")->object()->base();
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());

		object->insert(index, value, storage, exception, expr);
		return Query::ExceptionManager::has(exception) ? nullptr : PrimitiveFactory::createVoid();
	});

	type->addExternalCall("3", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= object->entries_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		object->erase(index);
		return PrimitiveFactory::createVoid();
	});

	type->addExternalCall("4", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		object->clear();
		return PrimitiveFactory::createVoid();
	});

	type->addExternalCall("5", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(object->empty());
	});

	type->addExternalCall("6", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createUInt(object->size());
	});

	type->addExternalCall("7", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<ArrayObject *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto size = static_cast<int>(Query::Object::getIndex(storage->findMemory("size")->object()));
		if (size < 0){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Negative size is not allowed!", expr)));
		}

		object->size(size);
		return PrimitiveFactory::createVoid();
	});
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::ArrayObject::add_(MemoryListType::iterator where, IType::Ptr type){
	auto storage = (Primitive::memory_ == nullptr) ? nullptr : Primitive::memory_->storage();
	return *entries_.emplace(entries_.end(), std::make_shared<StructuredScript::Storage::Memory>(storage, type, nullptr, nullptr));
}

StructuredScript::IType::Ptr StructuredScript::Objects::ArrayObject::class_;

StructuredScript::INode::Ptr StructuredScript::Objects::ArrayObject::lengthNode_;

const StructuredScript::Objects::ArrayObject::MemoryListType &StructuredScript::Objects::ArrayObject::list() const{
	return entries_;
}
