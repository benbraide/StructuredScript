#include "ExceptionManagerQuery.h"

void StructuredScript::Query::ExceptionManager::clear(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->clear();
}

void StructuredScript::Query::ExceptionManager::set(IExceptionManager *xManager, IAny::Ptr exception){
	if (xManager != nullptr)
		xManager->set(exception);
}

StructuredScript::IAny::Ptr StructuredScript::Query::ExceptionManager::setAndReturnObject(IExceptionManager *xManager, IAny::Ptr exception){
	set(xManager, exception);
	return nullptr;
}

StructuredScript::INode::Ptr StructuredScript::Query::ExceptionManager::setAndReturnNode(IExceptionManager *xManager, IAny::Ptr exception){
	set(xManager, exception);
	return nullptr;
}

std::string StructuredScript::Query::ExceptionManager::combine(const std::string &exception, INode *expr){
	return (expr == nullptr) ? exception : (exception + " -> '" + expr->str() + "'");
}

void StructuredScript::Query::ExceptionManager::setOnce(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->setOnce();
}

void StructuredScript::Query::ExceptionManager::setExit(IExceptionManager *xManager, IAny::Ptr value){
	if (xManager != nullptr)
		xManager->setExit(value);
}

void StructuredScript::Query::ExceptionManager::setReturn(IExceptionManager *xManager, IAny::Ptr value){
	if (xManager != nullptr)
		xManager->setReturn(value);
}

void StructuredScript::Query::ExceptionManager::setBreak(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->setBreak();
}

void StructuredScript::Query::ExceptionManager::setContinue(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->setContinue();
}

StructuredScript::IAny::Ptr StructuredScript::Query::ExceptionManager::get(IExceptionManager *xManager){
	return (xManager == nullptr) ? nullptr : xManager->get();
}

bool StructuredScript::Query::ExceptionManager::has(IExceptionManager *xManager){
	return (xManager == nullptr) ? false : xManager->has();
}

bool StructuredScript::Query::ExceptionManager::hasOnce(IExceptionManager *xManager){
	return (xManager == nullptr) ? false : xManager->hasOnce();
}

bool StructuredScript::Query::ExceptionManager::hasExit(IExceptionManager *xManager){
	return (xManager == nullptr) ? false : xManager->hasExit();
}

bool StructuredScript::Query::ExceptionManager::hasReturn(IExceptionManager *xManager){
	return (xManager == nullptr) ? false : xManager->hasExit();
}

bool StructuredScript::Query::ExceptionManager::hasBreak(IExceptionManager *xManager){
	return (xManager == nullptr) ? false : xManager->hasBreak();
}

bool StructuredScript::Query::ExceptionManager::hasContinue(IExceptionManager *xManager){
	return (xManager == nullptr) ? false : xManager->hasContinue();
}
