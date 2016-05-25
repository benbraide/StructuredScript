#include "Globals.h"

void StructuredScript::Globals::init(){
	std::string lines;

	lines += "@[Call(0)]any require(const ref val string path);";
	lines += "@[Call(1)]any require_once(const ref val string path);";
	lines += "@[Call(2)]any parse(const ref val string value);";
	lines += "@[Call(3)]any get_memory(const ref any object);";
	lines += "@[Call(4)]any get_storage(const ref any object);";

	lines += "any global_storage{ @[Call(9)]any get() }";
	lines += "any current_storage{ @[Call(10)]any get() }";

	auto parsed = IGlobalStorage::globalStorage->parse(lines);
	parsed->evaluate(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), nullptr, nullptr);

	IGlobalStorage::globalStorage->addExternalCall("0", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//require
		auto path = storage->findMemory("path")->object()->str(storage, exception, expr);
		if (!path_.empty())//Prepend base path
			path = path_ + "/" + path;

		return require_(path, storage, exception, expr);
	});

	IGlobalStorage::globalStorage->addExternalCall("1", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//require_once
		auto path = storage->findMemory("path")->object()->str(storage, exception, expr);
		if (!path_.empty())//Prepend base path
			path = path_ + "/" + path;

		for (auto &c : path){
			if (c == '\\')
				c = '/';
		}

		auto index = path.find("//");
		while (index < path.size()){
			path.erase(index, 1);
			index = path.find("//", index);
		}

		if (std::find(paths_.begin(), paths_.end(), path) == paths_.end()){//Not in list - require
			auto value = require_(path, storage, exception, expr);
			if (!Query::ExceptionManager::has(exception)){
				paths_.push_back(path);//Add to list
				return value;
			}

			return nullptr;
		}

		return PrimitiveFactory::createUndefined();//Already required
	});

	IGlobalStorage::globalStorage->addExternalCall("2", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//parse
		auto value = storage->findMemory("value")->object()->str(storage, exception, expr);
		auto parsed = IGlobalStorage::globalStorage->parse(value);
		if (parsed == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("There were errors while parsing!", expr)));
		}

		return PrimitiveFactory::createNodeObject(parsed);
	});

	IGlobalStorage::globalStorage->addExternalCall("3", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//get_memory
		auto memory = storage->findMemory("object")->object()->base()->memory();
		return PrimitiveFactory::createMemoryObject((memory == nullptr) ? nullptr : memory->ptr());
	});

	IGlobalStorage::globalStorage->addExternalCall("4", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//get_storage
		return PrimitiveFactory::createStorageObject(storage->findMemory("object")->object()->base()->memory()->storage());
	});

	IGlobalStorage::globalStorage->addExternalCall("9", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//global_storage.get
		return PrimitiveFactory::createStorageObject(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage));
	});

	IGlobalStorage::globalStorage->addExternalCall("10", [](IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{//current_storage.get
		while (storage != nullptr){//Find function storage - from property's get method
			if (dynamic_cast<IFunctionStorage *>(storage) == nullptr)
				storage = storage->parent();
			else
				break;
		}

		if (storage == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("Could not deduce current storage!", expr)));
		}

		return PrimitiveFactory::createStorageObject(storage->parent());
	});
}

void StructuredScript::Globals::path(const std::string &path){
	path_ = path;
}

StructuredScript::IAny::Ptr StructuredScript::Globals::require_(const std::string &path, IStorage *storage, IExceptionManager *exception, INode *expr){
	Parser::Parser parser;
	Scanner::Scanner scanner;

	ExceptionManager xManager;
	Scanner::FileCharacterWell well(path);
	if (well.fail()){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("Could not open file!", expr)));
	}

	auto parsed = parser.parse(well, scanner, &xManager);
	if (xManager.has()){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine(xManager.get()->str(storage, exception, expr), expr)));
	}

	parsed->evaluate(dynamic_cast<IStorage *>(IGlobalStorage::globalStorage), &xManager, expr);
	if (xManager.hasReturn())
		return xManager.get();

	if (xManager.has()){
		if (xManager.hasBreak()){
			Query::ExceptionManager::setBreak(exception);
			return nullptr;
		}

		if (xManager.hasContinue()){
			Query::ExceptionManager::setContinue(exception);
			return nullptr;
		}

		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine(xManager.get()->str(storage, exception, expr), expr)));
	}

	return PrimitiveFactory::createUndefined();
}

std::string StructuredScript::Globals::path_;

StructuredScript::Globals::PathListType StructuredScript::Globals::paths_;
