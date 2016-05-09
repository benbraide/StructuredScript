#include "Query.h"

void StructuredScript::Query::ExceptionManager::clear(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->clear();
}

void StructuredScript::Query::ExceptionManager::set(IExceptionManager *xManager, IAny::Ptr exception){
	if (xManager != nullptr)
		xManager->set(exception);
}

void StructuredScript::Query::ExceptionManager::setOnce(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->setOnce();
}

void StructuredScript::Query::ExceptionManager::setExit(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->setExit();
}

void StructuredScript::Query::ExceptionManager::setReturn(IExceptionManager *xManager){
	if (xManager != nullptr)
		xManager->setReturn();
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

bool StructuredScript::Query::Type::isAny(const IType *type){
	return (dynamic_cast<const IAnyType *>(type) != nullptr);
}
