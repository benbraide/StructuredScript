#include "ExceptionManager.h"

void StructuredScript::ExceptionManager::clear(){
	exception_ = nullptr;
	code_ = NONE;
}

void StructuredScript::ExceptionManager::suppress(){
	if (exception_ != nullptr && code_ == NONE)
		code_ = SUPPRESSED;
}

bool StructuredScript::ExceptionManager::unsuppress(){
	if (code_ == SUPPRESSED){
		code_ = NONE;
		return true;
	}

	return false;
}

void StructuredScript::ExceptionManager::set(IAny::Ptr exception){
	exception_ = exception;
}

void StructuredScript::ExceptionManager::setOnce(){
	code_ = ONCE;
}

void StructuredScript::ExceptionManager::setExit(IAny::Ptr value){
	code_ = EXIT;
	exception_ = value;
}

void StructuredScript::ExceptionManager::setReturn(IAny::Ptr value){
	code_ = RETURN;
	exception_ = value;
}

void StructuredScript::ExceptionManager::setBreak(){
	code_ = BREAK;
}

void StructuredScript::ExceptionManager::setContinue(){
	code_ = CONTINUE;
}

StructuredScript::IAny::Ptr StructuredScript::ExceptionManager::get() const{
	return exception_;
}

bool StructuredScript::ExceptionManager::has() const{
	return (exception_ != nullptr || (code_ != NONE && code_ != SUPPRESSED));
}

bool StructuredScript::ExceptionManager::hasOnce() const{
	return (code_ == ONCE);
}

bool StructuredScript::ExceptionManager::hasExit() const{
	return (code_ == EXIT);
}

bool StructuredScript::ExceptionManager::hasReturn() const{
	return (code_ == RETURN);
}

bool StructuredScript::ExceptionManager::hasBreak() const{
	return (code_ == BREAK);
}

bool StructuredScript::ExceptionManager::hasContinue() const{
	return (code_ == CONTINUE);
}
