#include "FunctionMemory.h"

StructuredScript::Storage::FunctionMemory::FunctionMemory(const ListType &components, IStorage *storage /*= nullptr*/)
	: storage_(storage){//Combine multiple function memories into one
	init_(components);

	auto owner = dynamic_cast<IAny *>(storage);
	if (owner != nullptr)//Store strong reference for temp objects
		owner_ = owner->ptr();
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::FunctionMemory::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::FunctionMemory::clone(){
	return std::make_shared<FunctionMemory>(list_, storage_);
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
	auto owner = dynamic_cast<IAny *>(storage);
	owner_ = (owner == nullptr) ? nullptr : owner->ptr();//Store strong reference for temp objects
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::add(IAny::Ptr function, IMemoryAttributes::Ptr attributes){
	auto functionBase = function->base();
	auto functionObject = dynamic_cast<IFunction *>(functionBase.get());
	if (functionObject == nullptr)//Function is required
		return nullptr;

	auto existing = find_(function);
	if (existing != list_.end()){//Replace existing only if existing is declaration and new is not
		auto existingFunction = dynamic_cast<IFunction *>(existing->value.get());
		if (existingFunction->isDefined() || !functionObject->isDefined())
			return nullptr;

		auto attributes = existing->memory->attributes();
		if (attributes != nullptr && (attributes->hasAttribute("Locked") || attributes->hasAttribute("Call")))//Restricted | Defined
			return nullptr;

		auto existingType = existingFunction->declaredType();
		auto newType = functionObject->declaredType();

		auto existingDeclaredType = dynamic_cast<IDeclaredType *>(existingType.get());
		auto newDeclaredType = dynamic_cast<IDeclaredType *>(newType.get());

		if (existingDeclaredType != nullptr){
			if (newDeclaredType == nullptr || existingDeclaredType->states() != newDeclaredType->states())
				return nullptr;//States must match previous declaration
		}
		else if (newDeclaredType != nullptr)
			return nullptr;//Declared status must match

		if (existingType->isAny() != newType->isAny() || !existingType->isEqual(newType))
			return nullptr;//Types must be 'explicitly' equal

		existing->memory->assign(function, nullptr, nullptr, nullptr);
		return existing->memory;
	}

	auto info = list_.emplace(list_.end(), IStorage::MemoryInfo{ nullptr, nullptr });
	auto memory = std::make_shared<StructuredScript::Storage::Memory>(&*info, storage_, IGlobalStorage::globalStorage->getPrimitiveType(
		Typename::TYPE_NAME_FUNCTION), attributes);

	info->memory = memory;
	memory->assign(function);//Assign function to memory

	return memory;
}

bool StructuredScript::Storage::FunctionMemory::remove(Memory::Ptr function){
	for (auto item = list_.begin(); item != list_.end(); ++item){
		if (item->memory == function){
			list_.erase(item);
			return true;
		}
	}

	return false;
}

StructuredScript::IAny::Ptr StructuredScript::Storage::FunctionMemory::call(bool rightUnary, const IFunction::ArgListType &args, IExceptionManager *exception, INode *expr){
	auto match = find(rightUnary, args);
	if (match == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("No function found taking the specified arguments!", expr)));
	}

	auto objectStorage = dynamic_cast<IAny *>(storage_);
	auto object = (objectStorage == nullptr) ? nullptr : objectStorage->ptr();

	return dynamic_cast<IFunction *>(match->object().get())->call(rightUnary, object, args, exception, expr);
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::find(bool rightUnary, const IFunction::ArgListType &args){
	auto max = 0;
	Ptr selected;

	auto objectStorage = dynamic_cast<IAny *>(storage_);
	auto object = (objectStorage == nullptr) ? nullptr : objectStorage->ptr();

	for (auto function = list_.rbegin(); function != list_.rend(); ++function){//Get function with highest score
		auto functionBase = function->memory->object()->base();
		auto score = dynamic_cast<IFunction *>(functionBase.get())->score(rightUnary, object, args);
		if (score > 0 && score >= max){
			max = score;
			selected = function->memory;
		}
	}

	return selected;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::find(bool rightUnary, const IFunction::TypeListType &args){
	auto max = 0;
	Ptr selected;

	auto objectStorage = dynamic_cast<IAny *>(storage_);
	auto object = (objectStorage == nullptr) ? nullptr : objectStorage->ptr();

	for (auto function = list_.rbegin(); function != list_.rend(); ++function){//Get function with highest score
		auto functionBase = function->memory->object()->base();
		auto score = dynamic_cast<IFunction *>(functionBase.get())->score(rightUnary, object, args);
		if (score > 0 && score >= max){
			max = score;
			selected = function->memory;
		}
	}

	return selected;
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::FunctionMemory::first(){
	return list_.empty() ? nullptr : list_.begin()->memory;
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::FunctionMemory::filterNonMembers(){
	ListType members, nonMembers;
	for (auto function : list_){
		if (dynamic_cast<IFunction *>(function.memory->object().get())->isMember())
			members.push_back(function);
		else
			nonMembers.push_back(function);
	}

	//Replace list with members only
	list_ = std::move(members);

	return nonMembers.empty() ? nullptr : std::make_shared<FunctionMemory>(nonMembers);
}

void StructuredScript::Storage::FunctionMemory::resolveArgs(INode::Ptr args, IFunction::ArgListType &resolved, IStorage *storage, IExceptionManager *exception, INode *expr){
	return resolveArgList(args, resolved, storage, exception, expr);
}

unsigned int StructuredScript::Storage::FunctionMemory::count() const{
	return list_.size();
}

void StructuredScript::Storage::FunctionMemory::getStaticMemories(ListType &list){
	for (auto memory : list_){
		auto type = memory.memory->type();
		auto declaredType = dynamic_cast<IDeclaredType *>(type.get());

		auto states = (declaredType == nullptr) ? StructuredScript::Storage::MemoryState::STATE_NONE : declaredType->states();
		if (StructuredScript::Storage::MemoryState(states).isStatic())
			list.push_back(memory);
	}
}

void StructuredScript::Storage::FunctionMemory::resolveArgList(INode::Ptr args, IFunction::ArgListType &resolved, IStorage *storage, IExceptionManager *exception, INode *expr){
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

void StructuredScript::Storage::FunctionMemory::init_(const ListType &components){
	for (auto component : components){
		auto functionMemory = dynamic_cast<FunctionMemory *>(component.memory.get());
		if (functionMemory == nullptr)
			list_.push_back({ component.memory, component.memory->object() });
		else
			init_(functionMemory->list_);
	}
}

StructuredScript::Storage::FunctionMemory::ListType::iterator StructuredScript::Storage::FunctionMemory::find_(IAny::Ptr function){
	for (auto item = list_.begin(); item != list_.end(); ++item){
		auto functionBase = item->memory->object()->base();
		auto functionObject = dynamic_cast<IFunction *>(functionBase.get());
		if (functionObject != nullptr && functionObject->equals(function))
			return item;
	}

	return list_.end();
}
