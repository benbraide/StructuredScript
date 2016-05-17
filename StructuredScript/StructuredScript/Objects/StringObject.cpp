#include "StringObject.h"

StructuredScript::Objects::String::String(const std::string &value) : TypedPrimitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_STRING), value){
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

StructuredScript::IStorage *StructuredScript::Objects::String::parent(){
	if (type_ == nullptr)
		return (memory_ == nullptr) ? nullptr : memory_->storage();

	return type_->storage();
}

std::shared_ptr<StructuredScript::IStorage> *StructuredScript::Objects::String::addStorage(const std::string &name){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Objects::String::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == type_->name())
		return this;

	auto storage = dynamic_cast<IStorage *>(type_.get());
	return (storage == nullptr) ? nullptr : storage->findStorage(name, searchScope);
}

StructuredScript::IType::Ptr *StructuredScript::Objects::String::addType(const std::string &name){
	return nullptr;
}

StructuredScript::IType::Ptr StructuredScript::Objects::String::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto storage = dynamic_cast<IStorage *>(type_.get());
	return (storage == nullptr) ? nullptr : storage->findType(name, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::String::addMemory(const std::string &name){
	return (name == "length" && length_ == nullptr) ? &length_ : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::String::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == "length")
		return length_;

	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberMemory(name, searchScope);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::String::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberFunctionMemory(name, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::String::addOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::String::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberOperatorMemory(name, searchScope);
}

StructuredScript::IMemory::Ptr *StructuredScript::Objects::String::addTypenameOperatorMemory(const std::string &name){
	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::String::findTypenameOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto compoundType = dynamic_cast<ICompoundType *>(type_.get());
	return (compoundType == nullptr) ? nullptr : compoundType->findMemberTypenameOperatorMemory(name, searchScope);
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::String::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::String::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

StructuredScript::Objects::String::ExternalCallType StructuredScript::Objects::String::findExternalCall(const std::string &name){
	auto storage = dynamic_cast<IStorage *>(type_.get());
	return (storage == nullptr) ? nullptr : storage->findExternalCall(name);
}

bool StructuredScript::Objects::String::remove(IMemory::Ptr target){
	return false;
}

void StructuredScript::Objects::String::init(std::shared_ptr<Type> type, IScanner &scanner, IParser &parser){
	std::list<std::string> lines({
		"@[Call(at)]char at(integral_type index)",
		"@[Call(append)]ref string append(const ref val string value)",
		"@[Call(insert)]ref string insert(integral_type index, const ref val string value)",
		"@[Call(erase)]ref string erase(integral_type index, integral_type count = npos)",
		"@[Call(clear)]void clear()",
		"@[Call(substr)]string substr(integral_type index, integral_type count = npos)",
		"@[Call(find)]int find(const ref val string value, integral_type offset = 0)",
		"@[Call(find_last)]int find_last(const ref val string value, integral_type offset = 0)",
		"@[Call(empty)]bool empty()",
		"static const unsigned int npos = -1u"
	});

	for (auto &line : lines){//Execute lines
		Scanner::StringCharacterWell well(line);
		parser.parse(well, scanner, nullptr)->evaluate(type.get(), nullptr, nullptr);
	}

	Scanner::StringCharacterWell well("any length{ @[Call(length.get)]unsigned int get() }");
	lengthNode_ = parser.parse(well, scanner, nullptr);

	type->addExternalCall("at", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= string->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		return PrimitiveFactory::createChar(string->value_[index]);
	});

	type->addExternalCall("append", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		string->value_.append(value->value_);
		return string->ptr();
	});

	type->addExternalCall("insert", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= string->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		string->value_.insert(index, value->value_);
		return string->ptr();
	});

	type->addExternalCall("erase", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= string->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		string->value_.erase(index, Query::Object::getIndex(storage->findMemory("count")->object()));
		return string->ptr();
	});

	type->addExternalCall("clear", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		string->value_.clear();
		return PrimitiveFactory::createVoid();
	});

	type->addExternalCall("substr", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto index = Query::Object::getIndex(storage->findMemory("index")->object());
		if (index >= string->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Index is out of bounds!", expr)));
		}

		return std::make_shared<String>(string->value_.substr(index, Query::Object::getIndex(storage->findMemory("count")->object())));
	});

	type->addExternalCall("find", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto offset = Query::Object::getIndex(storage->findMemory("offset")->object());
		if (offset >= string->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Offset is out of bounds!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		return PrimitiveFactory::createUInt(string->value_.find(value->value_, offset));
	});

	type->addExternalCall("find_last", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		auto offset = Query::Object::getIndex(storage->findMemory("offset")->object());
		if (offset >= string->value_.size()){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Offset is out of bounds!", expr)));
		}

		auto valueBase = storage->findMemory("value")->object()->base();
		auto value = dynamic_cast<String *>(valueBase.get());
		if (value == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Error while calling function!", expr)));
		}

		return PrimitiveFactory::createUInt(string->value_.find_last_of(value->value_, offset));
	});

	type->addExternalCall("empty", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createBool(string->value_.empty());
	});

	type->addExternalCall("length.get", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		auto storageBase = Query::Object::getObjectInStorage(storage)->base();
		auto string = dynamic_cast<String *>(storageBase.get());
		if (string == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Bad member function call!", expr)));
		}

		return PrimitiveFactory::createUInt(string->value_.size());
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

StructuredScript::INode::Ptr StructuredScript::Objects::String::lengthNode_;
