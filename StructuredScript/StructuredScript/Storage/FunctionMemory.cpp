#include "FunctionMemory.h"

StructuredScript::Storage::FunctionMemory::FunctionMemory(const ListType &components)
	: storage_(nullptr){//Combine multiple function memories into one
	for (auto component : components){
		auto functionMemory = dynamic_cast<FunctionMemory *>(component.get());
		if (functionMemory != nullptr){
			for (auto memory : functionMemory->list_)
				list_.push_back(memory);
		}
		else if (dynamic_cast<IFunction *>(component->object().get()) != nullptr)
			list_.push_back(component);
	}
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::FunctionMemory::ptr(){
	return shared_from_this();
}

void StructuredScript::Storage::FunctionMemory::assign(IAny::Ptr object, IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Invalid assignment!", expr)));
}

StructuredScript::IAny::Ptr StructuredScript::Storage::FunctionMemory::object(){
	return nullptr;
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::Storage::FunctionMemory::type(){
	return nullptr;
}

StructuredScript::Interfaces::MemoryAttributes::Ptr StructuredScript::Storage::FunctionMemory::attributes(){
	return nullptr;
}

StructuredScript::IStorage *StructuredScript::Storage::FunctionMemory::storage(){
	return storage_;
}

void StructuredScript::Storage::FunctionMemory::setStorage(IStorage *storage){
	storage_ = storage;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::add(IAny::Ptr function, IMemoryAttributes::Ptr attributes){
	auto functionBase = function->base();
	auto functionObject = dynamic_cast<IFunction *>(functionBase.get());
	if (functionObject == nullptr)//Function is required
		return nullptr;

	auto existing = find_(function);
	if (existing != list_.end()){//Replace existing only if existing is declaration and new is not
		auto existingBase = (*existing)->object()->base();
		if (dynamic_cast<IFunction *>(existingBase.get())->isDefined() || !functionObject->isDefined())
			return nullptr;

		auto attributes = (*existing)->attributes();
		if (attributes != nullptr && (attributes->hasAttribute("Locked") || attributes->hasAttribute("Call")))//Restricted | Defined
			return nullptr;

		(*existing)->assign(function, nullptr, nullptr, nullptr);
		return *existing;
	}

	list_.push_back(std::make_shared<StructuredScript::Storage::Memory>(storage_, IGlobalStorage::globalStorage->getPrimitiveType(
		Typename::TYPE_NAME_FUNCTION), nullptr, attributes));

	//Assign function to memory
	(*list_.rbegin())->assign(function, nullptr, nullptr, nullptr);

	return *list_.rbegin();
}

bool StructuredScript::Storage::FunctionMemory::remove(Memory::Ptr function){
	for (auto item = list_.begin(); item != list_.end(); ++item){
		if (*item == function){
			list_.erase(item);
			return true;
		}
	}

	return false;
}

StructuredScript::IAny::Ptr StructuredScript::Storage::FunctionMemory::call(bool rightUnary, const IFunction::ArgListType &args, IExceptionManager *exception, INode *expr){
	auto objectStorage = dynamic_cast<IAny *>(storage_);
	auto object = (objectStorage == nullptr) ? nullptr : objectStorage->ptr();

	auto match = find(rightUnary, object, args);
	if (match == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("No function found taking the specified arguments!", expr)));
	}

	return dynamic_cast<IFunction *>(match->object().get())->call(rightUnary, object, args, exception, expr);
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::find(bool rightUnary, IAny::Ptr object, const IFunction::ArgListType &args){
	auto max = 0;
	Ptr selected;

	for (auto function = list_.rbegin(); function != list_.rend(); ++function){//Get function with highest score
		auto functionBase = (*function)->object()->base();
		auto score = dynamic_cast<IFunction *>(functionBase.get())->score(rightUnary, object, args);
		if (score > 0 && score >= max){
			max = score;
			selected = *function;
		}
	}

	return selected;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::find(bool rightUnary, IAny::Ptr object, const IFunction::TypeListType &args){
	auto max = 0;
	Ptr selected;

	for (auto function = list_.rbegin(); function != list_.rend(); ++function){//Get function with highest score
		auto functionBase = (*function)->object()->base();
		auto score = dynamic_cast<IFunction *>(functionBase.get())->score(rightUnary, object, args);
		if (score > 0 && score >= max){
			max = score;
			selected = *function;
		}
	}

	return selected;
}

StructuredScript::Storage::Memory::Ptr StructuredScript::Storage::FunctionMemory::first(){
	return list_.empty() ? nullptr : *list_.begin();
}

void StructuredScript::Storage::FunctionMemory::resolveArgs(INode::Ptr args, IFunction::ArgListType &resolved, IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::Node::ListType list;
	Query::Node::split(",", args, list);

	for (auto arg : list){
		auto value = arg->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			break;

		if (Query::Object::isUndefined(value) || Query::Object::isExpansion(value)){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + arg->str() + "': Bad argument to function call!", expr)));

			break;
		}

		auto expanded = dynamic_cast<IExpanded *>(value.get());
		if (expanded == nullptr)
			resolved.push_back(value);
		else//Expand value
			expanded->expand(resolved);
	}
}

unsigned int StructuredScript::Storage::FunctionMemory::count() const{
	return list_.size();
}

void StructuredScript::Storage::FunctionMemory::getStaticMemories(ListType &list){
	for (auto memory : list_){
		auto type = memory->type();
		auto declaredType = dynamic_cast<IDeclaredType *>(type.get());

		auto states = (declaredType == nullptr) ? StructuredScript::Storage::MemoryState::STATE_NONE : declaredType->states();
		if (StructuredScript::Storage::MemoryState(states).isStatic())
			list.push_back(memory);
	}
}

StructuredScript::Storage::FunctionMemory::ListType::iterator StructuredScript::Storage::FunctionMemory::find_(IAny::Ptr function){
	for (auto item = list_.begin(); item != list_.end(); ++item){
		auto functionBase = (*item)->object()->base();
		auto functionObject = dynamic_cast<IFunction *>(functionBase.get());
		if (functionObject != nullptr && functionObject->equals(function))
			return item;
	}

	return list_.end();
}
