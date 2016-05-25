#include "Object.h"

StructuredScript::Objects::Object::~Object(){
	if (self_ != nullptr){//Only call destructors on fully constructed objects
		auto destructorMemory = dynamic_cast<IClass *>(type_.get())->destructor();
		if (destructorMemory != nullptr){
			auto functionMemory = dynamic_cast<IFunctionMemory *>(destructorMemory.get());
			if (functionMemory != nullptr){
				auto destructor = functionMemory->first();
				if (destructor != nullptr)
					dynamic_cast<IFunction *>(destructor->object().get())->rawCall(false, this, {}, nullptr, nullptr);
			}
		}

		self_ = nullptr;
	}
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Object::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto function = findOperatorMemory("*");
	auto value = callFunction_(function, nullptr, false, "", true, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (value != nullptr)
		return value;

	//Default clone
	auto object = std::make_shared<Object>(type_);
	for (auto &parent : parents_){
		auto parentClone = parent.second.value->clone(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		auto memory = parent.second.memory;
		auto info = object->addParent(parent.first);

		auto newMemory = std::make_shared<StructuredScript::Storage::Memory>(info, object.get(), memory->type(), memory->attributes());
		newMemory->assign(parentClone);
		info->memory = newMemory;
	}

	for (auto &entry : objects_){
		auto property = dynamic_cast<IProperty *>(entry.second.value.get());

		Ptr objectClone;
		if (property == nullptr)
			objectClone = entry.second.value->clone(storage, exception, expr);
		else//Clone property object
			objectClone = property->propertyClone(storage, exception, expr);

		if (Query::ExceptionManager::has(exception))
			return nullptr;

		auto memory = entry.second.memory;
		auto info = object->addMemory(entry.first);

		auto newMemory = std::make_shared<StructuredScript::Storage::Memory>(info, object.get(), memory->type(), memory->attributes());
		newMemory->assign(objectClone);
		info->memory = newMemory;
	}

	object->self_ = object.get();//Signal full construction
	return object;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Object::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	auto function = findTypenameOperatorMemory(type);
	auto value = callFunction_(function, nullptr, false, "", true, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (value != nullptr)
		return value;

	return type_->isEqual(type) ? shared_from_this() : nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Object::assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	auto function = findOperatorMemory(value);
	auto returnValue = callFunction_(function, nullptr, false, "", true, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (returnValue != nullptr)
		return returnValue;

	//Default assignent
	if (memory_ == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Assignment requires an lvalue object!", expr)));
	}

	if (value.size() > 1u){//Compound assignment
		right = evaluateBinary(value.substr(0, value.size() - 1), right, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	auto memory = memory_;
	memory->assign(right, storage, exception, expr);

	return Query::ExceptionManager::has(exception) ? nullptr : memory->object();
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Object::evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (value == "&" || value == "*"){
		auto function = findOperatorMemory(value);
		auto returnValue = callFunction_(function, nullptr, false, "", true, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;

		return (returnValue == nullptr) ? Any::evaluateLeftUnary(value, storage, exception, expr) : returnValue;
	}

	auto function = findOperatorMemory(value);
	return callFunction_(function, nullptr, false, value, false, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Object::evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	auto function = findOperatorMemory(value);
	return callFunction_(function, nullptr, true, value, false, exception, expr);
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Object::evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	using StructuredScript::Storage::FunctionMemory;

	auto rightBase = right->base();
	if (rightBase == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Operands mismatch!", expr)));
	}

	auto function = findOperatorMemory(value);
	auto rightObject = dynamic_cast<IStorage *>(rightBase.get());
	if (rightObject != nullptr){//Get operators from 'right'
		auto rightFunction = rightObject->findOperatorMemory(value);
		if (function != nullptr && rightFunction != nullptr)
			function = std::make_shared<FunctionMemory>(FunctionMemory::ListType{ {function, nullptr}, {rightFunction, nullptr} });
		else if (rightFunction != nullptr)
			function = rightFunction;
	}

	return callFunction_(function, rightBase, false, value, false, exception, expr);
}

bool StructuredScript::Objects::Object::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	return false;
}

std::string StructuredScript::Objects::Object::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	return "";
}

StructuredScript::IStorage *StructuredScript::Objects::Object::findStorage(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name == type_->name())
		return this;

	if (searchScope != SEARCH_LOCAL){
		for (auto &parent : parents_){
			auto storage = dynamic_cast<IStorage *>(parent.second.value.get())->findStorage(name, SEARCH_FAMILY);
			if (storage != nullptr)
				return storage;
		}
	}

	if (self_ == nullptr || self_ == this)
		return (searchScope == SEARCH_DEFAULT) ? dynamic_cast<IStorage *>(type_.get())->findStorage(name) : nullptr;

	return self_->findStorage(name, searchScope);
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Objects::Object::addMemory(const std::string &name){
	return (objects_.find(name) == objects_.end()) ? &objects_[name] : nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	auto object = objects_.find(name);
	if (object != objects_.end()){
		if (memory_ == nullptr){//Temp object
			auto property = dynamic_cast<IProperty *>(object->second.value.get());
			if (property != nullptr)
				property->setOwner(ptr());
		}

		return object->second.memory;//Target is a member object
	}

	auto memory = dynamic_cast<IStorage *>(type_.get())->findMemory(name, SEARCH_LOCAL);
	if (memory != nullptr && dynamic_cast<IFunctionMemory *>(memory.get()) == nullptr)
		return memory;//Target is a static object

	ListType list;
	if (memory != nullptr)
		list.push_back({ memory, nullptr });

	extendList_(list, name, searchScope);

	return std::make_shared<StructuredScript::Storage::FunctionMemory>(list, this);
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findFunctionMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;

	auto memory = dynamic_cast<IStorage *>(type_.get())->findFunctionMemory(name, SEARCH_LOCAL);//Search type
	if (memory != nullptr)
		list.push_back({memory, nullptr});

	extendList_(list, name, searchScope);
	if (!list.empty())
		return std::make_shared<StructuredScript::Storage::FunctionMemory>(list, this);

	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findOperatorMemory(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;
	extendOperatorList_(list, name, searchScope);
	if (!list.empty())
		return std::make_shared<StructuredScript::Storage::FunctionMemory>(list, this);

	return nullptr;
}

StructuredScript::IMemory::Ptr StructuredScript::Objects::Object::findTypenameOperatorMemory(IType::Ptr name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	ListType list;
	extendTypeOperatorList_(list, name, searchScope);
	if (!list.empty())
		return std::make_shared<StructuredScript::Storage::FunctionMemory>(list, this);

	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr *StructuredScript::Objects::Object::addMemoryAttribute(const std::string &name){
	return nullptr;
}

StructuredScript::IMemoryAttribute::Ptr StructuredScript::Objects::Object::findMemoryAttribute(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	return nullptr;
}

bool StructuredScript::Objects::Object::remove(IMemory::Ptr target){
	return false;
}

void StructuredScript::Objects::Object::construct(const IFunction::ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (self_ != nullptr){//Already constructed
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Cannot construct a fully constructed object!", expr)));

		return;
	}

	auto constructorMemory = dynamic_cast<IClass *>(type_.get())->constructor();
	if (constructorMemory == nullptr){//Nothing to construct
		if (!args.empty()){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"No constructor found taking the specified arguments!", expr)));
		}

		self_ = this;//No constructor -- fully constructed
		constructParents_(storage, exception, expr);

		return;
	}

	auto functionMemory = dynamic_cast<IFunctionMemory *>(constructorMemory.get());
	if (functionMemory != nullptr){
		functionMemory->setStorage(this);
		functionMemory->call(false, args, exception, expr);
		if (!Query::ExceptionManager::has(exception)){//Fully constructed
			self_ = this;
			constructParents_(storage, exception, expr);
		}
	}
	else{
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"No constructor found taking the specified arguments!", expr)));
	}
}

StructuredScript::IObject *StructuredScript::Objects::Object::findDirectParent(const std::string &name){
	auto parent = parents_.find(name);
	return (parent == parents_.end()) ? nullptr : dynamic_cast<IObject *>(parent->second.value.get());
}

void StructuredScript::Objects::Object::self(Any *self){
	self_ = self;
}

StructuredScript::IStorage::MemoryInfo *StructuredScript::Objects::Object::addParent(const std::string &name){
	return (parents_.find(name) == parents_.end()) ? &parents_[name] : nullptr;
}

void StructuredScript::Objects::Object::extendList_(ListType &list, const std::string &name, unsigned short searchScope){
	if (self_ != nullptr && self_ != this){//Search linked object
		auto memory = self_->findFunctionMemory(name, (searchScope == SEARCH_LOCAL) ? SEARCH_LOCAL : SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back({memory, nullptr});
	}

	if (searchScope == SEARCH_LOCAL)
		return;//Ignore parents & global

	for (auto &parent : parents_){//Search parents
		auto memory = dynamic_cast<IStorage *>(parent.second.value.get())->findFunctionMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back({memory, nullptr});
	}

	if (searchScope == SEARCH_DEFAULT){//Search global
		if (type_->storage() != nullptr){//Prefer type's storage
			auto memory = type_->storage()->findFunctionMemory(name);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}
		else if (memory_->storage() != nullptr){//Type has no storage - try object's storage
			auto memory = memory_->storage()->findFunctionMemory(name);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}
	}
}

void StructuredScript::Objects::Object::extendOperatorList_(ListType &list, const std::string &name, unsigned short searchScope){
	auto memory = dynamic_cast<IStorage *>(type_.get())->findOperatorMemory(name, SEARCH_LOCAL);//Search type
	if (memory != nullptr)
		list.push_back({ memory, nullptr });

	if (self_ != nullptr && self_ != this){//Search linked object
		memory = self_->findOperatorMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	if (searchScope == SEARCH_LOCAL)
		return;//Ignore parents & global

	for (auto &parent : parents_){//Search parents
		memory = dynamic_cast<IStorage *>(parent.second.value.get())->findOperatorMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	if (searchScope == SEARCH_DEFAULT){//Search global
		if (type_->storage() != nullptr){//Prefer type's storage
			auto memory = type_->storage()->findOperatorMemory(name);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}
		else if (memory_->storage() != nullptr){//Type has no storage - try object's storage
			auto memory = memory_->storage()->findOperatorMemory(name);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}
	}
}

void StructuredScript::Objects::Object::extendTypeOperatorList_(ListType &list, IType::Ptr name, unsigned short searchScope){
	auto memory = dynamic_cast<IStorage *>(type_.get())->findTypenameOperatorMemory(name, SEARCH_LOCAL);//Search type
	if (memory != nullptr)
		list.push_back({ memory, nullptr });

	if (self_ != nullptr && self_ != this){//Search linked object
		memory = self_->findTypenameOperatorMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	if (searchScope == SEARCH_LOCAL)
		return;//Ignore parents & global

	for (auto &parent : parents_){//Search parents
		memory = dynamic_cast<IStorage *>(parent.second.value.get())->findTypenameOperatorMemory(name, SEARCH_FAMILY);
		if (memory != nullptr)
			list.push_back({ memory, nullptr });
	}

	if (searchScope == SEARCH_DEFAULT){//Search global
		if (type_->storage() != nullptr){//Prefer type's storage
			auto memory = type_->storage()->findTypenameOperatorMemory(name);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}
		else if (memory_->storage() != nullptr){//Type has no storage - try object's storage
			auto memory = memory_->storage()->findTypenameOperatorMemory(name);
			if (memory != nullptr)
				list.push_back({ memory, nullptr });
		}
	}
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Object::callFunction_(IMemory::Ptr function, Ptr right, bool isRight,
	const std::string &value, bool silent, IExceptionManager *exception, INode *expr){
	auto functionMemory = dynamic_cast<IFunctionMemory *>(function.get());
	if (functionMemory == nullptr){
		if (silent)
			return nullptr;

		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Operands mismatch!", expr)));
	}

	auto nonMembers = functionMemory->filterNonMembers();
	IFunction::ArgListType args;
	if (right != nullptr)
		args.push_back(right);

	auto memberMatch = functionMemory->find(isRight, args);
	if (memberMatch != nullptr)//Call member operator
		return dynamic_cast<IFunction *>(memberMatch->object().get())->call(isRight, shared_from_this(), args, exception, expr);

	if (nonMembers != nullptr){//Try non-members using object as argument
		args.push_front(shared_from_this());
		auto nonMemberMatch = dynamic_cast<IFunctionMemory *>(nonMembers.get())->find(isRight, args);
		if (nonMemberMatch != nullptr)//Call non-member operator
			return dynamic_cast<IFunction *>(nonMemberMatch->object().get())->call(isRight, nullptr, args, exception, expr);
	}

	if (silent)
		return nullptr;

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

void StructuredScript::Objects::Object::constructParents_(IStorage *storage, IExceptionManager *exception, INode *expr){
	for (auto &parent : parents_){
		auto object = dynamic_cast<Object *>(parent.second.value.get());
		if (object->self_ == nullptr){//Construct unconstructed parents
			object->construct({}, storage, exception, expr);
			if (Query::ExceptionManager::has(exception))
				return;
		}
	}
}
