#include "FunctionMemory.h"

StructuredScript::Storage::FunctionMemory::FunctionMemory(const ListType &components)
	: storage_(nullptr){//Combine multiple function memories into one
	for (auto component : components){
		auto functionMemory = dynamic_cast<FunctionMemory *>(component.get());
		if (functionMemory != nullptr){
			for (auto memory : functionMemory->list_)
				list_.push_back(memory);
		}
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
	auto functionObject = dynamic_cast<IFunction *>(function->base());
	if (functionObject == nullptr)//Function is required
		return nullptr;

	auto existing = find_(function);
	if (existing != list_.end()){//Replace existing only if existing is declaration and new is not
		if (dynamic_cast<IFunction *>((*existing)->object()->base())->isDefined() || !functionObject->isDefined())
			return nullptr;

		auto attributes = (*existing)->attributes();
		if (attributes != nullptr && (attributes->hasAttribute("Locked") || attributes->hasAttribute("Call")))//Restricted | Defined
			return nullptr;

		list_.erase(existing);
	}

	list_.push_back(std::make_shared<StructuredScript::Storage::Memory>(storage_, IGlobalStorage::globalStorage->getPrimitiveType(
		Typename::TYPE_NAME_FUNCTION), nullptr, attributes));

	//Assign function to memory
	(*list_.rbegin())->assign(function, nullptr, nullptr, nullptr);

	return *list_.rbegin();
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::find(const IFunction::ArgListType &args){
	auto max = 0;
	Ptr selected;

	for (auto function : list_){//Get function with highest score
		auto score = dynamic_cast<IFunction *>(function->object()->base())->score(args);
		if (score > 0 && score >= max){
			max = score;
			selected = function;
		}
	}

	return selected;
}

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::find(const IFunction::TypeListType &args){
	auto max = 0;
	Ptr selected;

	for (auto function : list_){//Get function with highest score
		auto score = dynamic_cast<IFunction *>(function->object()->base())->score(args);
		if (score > 0 && score >= max){
			max = score;
			selected = function;
		}
	}

	return selected;
}

void StructuredScript::Storage::FunctionMemory::resolveArgs(INode::Ptr args, IFunction::ArgListType &resolved, IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::Node::ListType list;
	Query::Node::split(",", args, list);

	for (auto arg : list){
		auto value = arg->evaluate(storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			break;

		if (Query::Object::isUndefined(value)){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'" + arg->str() + "': Bad argument to function call!", expr)));

			break;
		}

		resolved.push_back(value);
	}
}

StructuredScript::Storage::FunctionMemory::ListType::iterator StructuredScript::Storage::FunctionMemory::find_(IAny::Ptr function){
	for (auto item = list_.begin(); item != list_.end(); ++item){
		auto functionObject = dynamic_cast<IFunction *>((*item)->object()->base());
		if (functionObject != nullptr && functionObject->equals(function))
			return item;
	}

	return list_.end();
}
