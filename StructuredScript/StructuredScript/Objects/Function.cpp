#include "Function.h"

bool StructuredScript::Objects::Function::isDefined() const{
	return (definition_ != nullptr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Function::call(bool rightUnary, IAny::Ptr object, const ArgListType &args,
	IExceptionManager *exception, INode *expr){
	return rawCall(rightUnary, object.get(), args, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Function::rawCall(bool rightUnary, IAny *object, const ArgListType &args,
	IExceptionManager *exception, INode *expr){
	auto storage = (object == nullptr) ? memory_->storage() : dynamic_cast<IStorage *>(object);
	if (storage == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Bad function call!", expr)));
	}

	auto call = getExternalCall_(storage, exception, expr);
	if (call == nullptr && definition_ == nullptr){//Undefined without external call
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Cannot call an undefined function!", expr)));
	}

	auto parameterStorage = std::make_shared<Storage::RawFunctionStorage>(storage, object);
	auto expansionMemory = prep_(args, parameterStorage.get(), exception, expr);

	auto attributes = memory_->attributes();
	auto attribute = (attributes == nullptr) ? nullptr : attributes->getAttribute("Concurrent");
	if (attribute != nullptr){//Concurrent execution
		auto objectPtr = (object == nullptr) ? nullptr : object->ptr();
		auto t = std::thread([=](){
			call_(call, parameterStorage, expansionMemory, dynamic_cast<IObject *>(objectPtr.get()), storage, exception, expr);
		});

		t.detach();
		return PrimitiveFactory::createUndefined();
	}

	return call_(call, parameterStorage, expansionMemory, dynamic_cast<IObject *>(object), storage, exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Function::call_(IStorage::ExternalCallType call, std::shared_ptr<Storage::RawFunctionStorage> parameterStorage,
	IMemory::Ptr expansionMemory, IObject *object, IStorage *storage, IExceptionManager *exception, INode *expr){
	initialize(object, parameterStorage.get(), exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (call != nullptr)//Forward call
		return call(parameterStorage.get(), exception, expr);

	if (!Query::Node::isEmpty(definition_))
		definition_->evaluate(parameterStorage.get(), exception, expr);

	auto value = getReturnValue_(exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	if (type_ == nullptr){
		if (value != nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Invalid 'return' statement found in a constructor/destructor!", expr)));
		}

		return PrimitiveFactory::createUndefined();
	}

	IStorage::MemoryInfo info;
	auto memory = (value == nullptr) ? nullptr : value->memory();
	auto converter = std::make_shared<Storage::Memory>(&info, nullptr, type_, memory_->attributes());//For converting return value

	converter->assign((value == nullptr) ? PrimitiveFactory::createVoid() : value, storage, exception, expr);
	if (value != nullptr)//Restore memory
		value->setMemory(memory);

	return Query::ExceptionManager::has(exception) ? nullptr : info.value;
}

StructuredScript::IStorage::ExternalCallType StructuredScript::Objects::Function::getExternalCall_(IStorage *storage, IExceptionManager *exception, INode *expr){
	if (definition_ != nullptr)
		return nullptr;

	//Not defined -- check for 'Call' attribute

	auto attributes = (memory_ == nullptr) ? nullptr : memory_->attributes();
	if (attributes == nullptr)
		return nullptr;

	auto callAttribute = attributes->getAttribute("Call");//Check if there's a CallAttribute
	if (callAttribute == nullptr)
		return nullptr;

	return storage->findExternalCall(dynamic_cast<IAttributeWithArgument *>(callAttribute.get())->arg()->str());
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Function::getReturnValue_(IExceptionManager *exception, INode *expr){
	if (Query::ExceptionManager::hasReturn(exception)){
		auto value = exception->get();
		exception->clear();
		return value;
	}
	
	return nullptr;
}

void StructuredScript::Objects::Function::initialize(IObject *object, IStorage *storage, IExceptionManager *exception, INode *expr){}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Constructor::call(bool rightUnary, IAny::Ptr object, const ArgListType &args,
	IExceptionManager *exception, INode *expr){
	if (rightUnary || object == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Bad constructor call!", expr)));
	}

	return Function::call(rightUnary, object, args, exception, expr);
}

void StructuredScript::Objects::Constructor::initialize(IObject *object, IStorage *storage, IExceptionManager *exception, INode *expr){
	auto objectStorage = dynamic_cast<IStorage *>(object);

	std::map< std::string, std::pair<IMemory::Ptr, INode::Ptr> > fields;
	for (auto &initializer : initializers_){
		auto target = objectStorage->findMemory(initializer.first, IStorage::SEARCH_LOCAL);
		if (target != nullptr){
			if (dynamic_cast<IFunctionMemory *>(target.get()) != nullptr){
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + initializer.first + "': Invalid initializer item!", expr)));
			}
			else
				fields[initializer.first] = std::make_pair(target, initializer.second);
		}
		else//Try base constructor
			initializeParent_(initializer, object, storage, exception, expr);
		
		if (Query::ExceptionManager::has(exception))
			return;
	}

	for (auto &field : fields){//Initialize fields after base constructors
		auto value = field.second.first->object();
		if (value != nullptr && !Query::Object::isUndefined(value)){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + field.first + "': Is already initialized!", expr)));

			return;
		}

		value = field.second.second->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return;

		field.second.first->assign(value, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return;
	}
}

void StructuredScript::Objects::Constructor::initializeParent_(const std::pair<std::string, INode::Ptr> &info, IObject *object,
	IStorage *storage, IExceptionManager *exception, INode *expr){
	auto parent = object->findDirectParent(info.first);
	if (parent == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'" + info.first + "': Invalid initializer item!", expr)));

		return;
	}

	ArgListType args;
	Storage::FunctionMemory::resolveArgList(info.second, args, storage, exception, expr);
	if (!Query::ExceptionManager::has(exception))
		parent->construct(args, storage, exception, expr);
}
