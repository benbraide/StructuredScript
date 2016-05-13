#include "FunctionMemory.h"

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

StructuredScript::IMemory::Ptr StructuredScript::Storage::FunctionMemory::add(IAny::Ptr function, IMemoryAttributes::Ptr attributes){
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
