#include "Function.h"

bool StructuredScript::Objects::Function::isDefined() const{
	return (definition_ != nullptr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Function::call(bool rightUnary, IAny::Ptr object, const ArgListType &args,
	IExceptionManager *exception, INode *expr){
	auto storage = (object == nullptr) ? memory_->storage() : dynamic_cast<IStorage *>(object.get());
	if (storage == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Bad function call!", expr)));
	}

	IStorage::ExternalCallType call = nullptr;
	if (definition_ == nullptr){//Not defined -- check for 'Call' attribute
		auto attributes = (memory_ == nullptr) ? nullptr : memory_->attributes();
		if (attributes == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot call an undefined function!", expr)));
		}

		auto callAttribute = attributes->getAttribute("Call");//Check if there's a CallAttribute
		if (callAttribute == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot call an undefined function!", expr)));
		}

		call = storage->findExternalCall(dynamic_cast<IAttributeWithArgument *>(callAttribute.get())->arg()->str());
		if (call == nullptr){//Undefined
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Cannot call an undefined function!", expr)));
		}
	}

	Storage::FunctionStorage parameterStorage(storage, object);
	auto expansionMemory = prep_(args, &parameterStorage, exception, expr);

	if (call != nullptr)//Forward call
		return call(&parameterStorage, exception, expr);

	if (!Query::Node::isEmpty(definition_))
		definition_->evaluate(&parameterStorage, exception, expr);

	Ptr value;//Return value
	if (Query::ExceptionManager::hasReturn(exception)){
		value = exception->get();
		if (value == nullptr && type_ != nullptr)
			value = PrimitiveFactory::createVoid();

		exception->clear();
	}
	else if (Query::ExceptionManager::hasBreak(exception)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'break' found outside loop!", expr)));
	}
	else if (Query::ExceptionManager::hasContinue(exception)){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'continue' found outside loop!", expr)));
	}
	else if (!Query::ExceptionManager::has(exception)){
		if (type_ != nullptr)
			value = PrimitiveFactory::createVoid();
	}
	else
		return nullptr;

	if (type_ == nullptr && value != nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Invalid 'return' statement found in a constructor/destrcutor!", expr)));
	}

	Storage::Memory converter(nullptr, type_, value, nullptr);//For converting return value
	converter.assign(value, storage, exception, expr);

	return Query::ExceptionManager::has(exception) ? nullptr : converter.object();
}
