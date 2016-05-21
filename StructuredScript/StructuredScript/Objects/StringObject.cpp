#include "StringObject.h"

StructuredScript::Objects::String::String(const std::string &value)
	: TypedPrimitive(class_, value), Objects::PrimitiveObject(class_, TypedPrimitive::memory_){
	lengthNode_->evaluate(this, nullptr, nullptr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::String::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<String>(value_);
}

bool StructuredScript::Objects::String::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return !value_.empty();
}

std::string StructuredScript::Objects::String::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return value_;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::String::evaluateBinary(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	if (value != "[]")
		return Primitive::evaluateBinary(value, right, storage, exception, expr);

	auto rightBase = right->base();
	if (dynamic_cast<IInteger *>(rightBase.get()) == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'[]': Expected index to be an integral value!", expr)));
	}

	auto index = Query::Object::getIndex(right);
	if (index >= value_.size()){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Index is out of bounds!", expr)));
	}

	return PrimitiveFactory::createLChar(value_[index]);
}

void StructuredScript::Objects::String::init(){
	std::string lines = "class @string{";

	lines += "@[Call(0)]char at(integral_type index);";
	lines += "@[Call(1)]ref string append(const ref val string value);";
	lines += "@[Call(2)]ref string insert(integral_type index, const ref val string value);";
	lines += "@[Call(3)]ref string erase(integral_type index, integral_type count = npos);";
	lines += "@[Call(4)]void clear();";
	lines += "@[Call(5)]string substr(integral_type index, integral_type count = npos);";
	lines += "@[Call(6)]int find(const ref val string value, integral_type offset = 0);";
	lines += "@[Call(7)]int find_last(const ref val string value, integral_type offset = 0);";
	lines += "@[Call(8)]bool empty();";
	lines += "static const unsigned int npos = -1u}";

	auto parsed = IGlobalStorage::globalStorage->parse(lines);

	class_ = dynamic_cast<IClassNode *>(parsed.get())->create(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), nullptr, nullptr);
	lengthNode_ = IGlobalStorage::globalStorage->parse("any length{ @[Call(9)]unsigned int get() }");

	auto type = dynamic_cast<Type *>(class_.get());

	type->addExternalCall("0", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= object->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		return PrimitiveFactory::createChar(object->value_[index]);
	});

	type->addExternalCall("1", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		object->value_.append(value->value_);
		return object->ptr();
	});

	type->addExternalCall("2", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= object->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		object->value_.insert(index, value->value_);
		return object->ptr();
	});

	type->addExternalCall("3", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= object->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		object->value_.erase(index, Query::Object::getIndex(storage->findMemory("count")->object()));
		return object->ptr();
	});

	type->addExternalCall("4", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		object->value_.clear();
		return PrimitiveFactory::createVoid();
	});

	type->addExternalCall("5", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= object->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		return std::make_shared<String>(object->value_.substr(index, Query::Object::getIndex(storage->findMemory("count")->object())));
	});

	type->addExternalCall("6", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto offset = Query::Object::getIndex(storage->findMemory("offset")->object());
		if (offset >= object->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Offset is out of bounds!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		return PrimitiveFactory::createUInt(object->value_.find(value->value_, offset));
	});

	type->addExternalCall("7", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto offset = Query::Object::getIndex(storage->findMemory("offset")->object());
		if (offset >= object->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Offset is out of bounds!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		return PrimitiveFactory::createUInt(object->value_.find_last_of(value->value_, offset));
	});

	type->addExternalCall("8", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(object->value_.empty());
	});

	type->addExternalCall("9", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto functionStorage = dynamic_cast<IFunctionStorage *>(storage);
		auto object = (functionStorage == nullptr) ? nullptr : dynamic_cast<String *>(functionStorage->object()->memory()->storage());
		if (object == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createUInt(object->value_.size());
	});
}

StructuredScript::IAny::Ptr StructuredScript::Objects::String::promote_(Primitive *target){
	switch (target->rank()){
	case Primitive::CHAR_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::CHAR_RANK>::type *>(target)->value()));
	case Primitive::UCHAR_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::UCHAR_RANK>::type *>(target)->value()));
	case Primitive::SHORT_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::SHORT_RANK>::type *>(target)->value()));
	case Primitive::USHORT_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::USHORT_RANK>::type *>(target)->value()));
	case Primitive::INT_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::INT_RANK>::type *>(target)->value()));
	case Primitive::UINT_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::UINT_RANK>::type *>(target)->value()));
	case Primitive::LONG_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::LONG_RANK>::type *>(target)->value()));
	case Primitive::ULONG_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::ULONG_RANK>::type *>(target)->value()));
	case Primitive::LLONG_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::LLONG_RANK>::type *>(target)->value()));
	case Primitive::ULLONG_RANK:
		return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::ULLONG_RANK>::type *>(target)->value()));
	case Primitive::FLOAT_RANK:
		return std::make_shared<String>(Float::toString(dynamic_cast<PrimitiveType<Primitive::FLOAT_RANK>::type *>(target)->value()));
	case Primitive::DOUBLE_RANK:
		return std::make_shared<String>(Double::toString(dynamic_cast<PrimitiveType<Primitive::DOUBLE_RANK>::type *>(target)->value()));
	case Primitive::LDOUBLE_RANK:
		return std::make_shared<String>(LDouble::toString(dynamic_cast<PrimitiveType<Primitive::LDOUBLE_RANK>::type *>(target)->value()));
	default:
		break;
	}

	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::String::evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr){
	auto leftBase = left->base(), rightBase = right->base();
	if (value == "+")
		return std::make_shared<String>(dynamic_cast<String *>(leftBase.get())->value_ + dynamic_cast<String *>(rightBase.get())->value_);

	return TypedPrimitive::evaluate_(value, left, right, exception, expr);
}

StructuredScript::IType::Ptr StructuredScript::Objects::String::class_;

StructuredScript::INode::Ptr StructuredScript::Objects::String::lengthNode_;
