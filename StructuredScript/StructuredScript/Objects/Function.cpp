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

void StructuredScript::Objects::Constructor::initialize(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto object = dynamic_cast<IObject *>(storage);
	if (object == nullptr){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Cannot initialize a non-object!", expr)));

		return;
	}

	std::map< std::string, std::pair<IMemory::Ptr, INode::Ptr> > fields;
	for (auto &initializer : initializers_){
		auto target = storage->findMemory(initializer.first, IStorage::SEARCH_LOCAL);
		if (target != nullptr){
			if (dynamic_cast<IFunctionMemory *>(target.get()) != nullptr){
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
					Query::ExceptionManager::combine("'" + initializer.first + "': Invalid initializer item!", expr)));

				return;
			}

			fields[initializer.first] = std::make_pair(target, initializer.second);
		}
		else//Try base constructor
			initializeParent_(initializer, object, storage, exception, expr);
		
		if (Query::ExceptionManager::has(exception))
			return;
	}

	for (auto &field : fields){//Initialize fields after base constructors
		if (field.second.first->object() != nullptr){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + field.first + "': Is already initialized!", expr)));

			return;
		}

		auto value = field.second.second->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return;

		field.second.first->assign(value, storage, exception, expr);
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
