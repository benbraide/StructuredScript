#include "Primitive.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot copy object!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr){
	return type->isEqual(type_) ? ptr() : nullptr;
}

StructuredScript::IAny *StructuredScript::Objects::Primitive::base(){
	return this;
}

StructuredScript::IType::Ptr StructuredScript::Objects::Primitive::type(){
	return type_;
}

void StructuredScript::Objects::Primitive::setMemory(IMemory *memory){
	memory_ = memory;
}

StructuredScript::IMemory *StructuredScript::Objects::Primitive::memory(){
	return memory_;
}

bool StructuredScript::Objects::Primitive::truth(IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot get truth value of object!", expr)));

	return false;
}

std::string StructuredScript::Objects::Primitive::str(IStorage *storage, IExceptionManager *exception, INode *expr){
	Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
		Query::ExceptionManager::combine("Cannot get string value of object!", expr)));

	return "";
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateBinary(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	if (value == "=" || value == "+=" || value == "-=" || value == "*=" || value == "/=" || value == "%=" || value == "&=" ||
		value == "^=" || value == "|=" || value == "<<=" || value == ">>="){//Assignment
		if (memory_ == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"'" + value + "': Assignment requires an lvalue object!", expr)));
		}

		if (value.size() > 1u){//Compound assignment
			right = evaluateBinary_(value.substr(0, value.size() - 1), right, storage, exception, expr);
			if (Query::ExceptionManager::has(exception))
				return nullptr;
		}

		auto memory = memory_;
		memory->assign(right, storage, exception, expr);

		return Query::ExceptionManager::has(exception) ? nullptr : memory->object();
	}

	return evaluateBinary_(value, right, storage, exception, expr);
}

int StructuredScript::Objects::Primitive::rank(){
	return -1;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::promote_(Primitive *target){
	return nullptr;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluate_(const std::string &value, bool reversed, Ptr right,
	IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateBinary_(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	auto primitive = dynamic_cast<Primitive *>(right->base());
	if (primitive == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Operands mismatch!", expr)));
	}

	auto left = prepForExpression_();
	auto primitiveLeft = dynamic_cast<Primitive *>(left->base());
	
	if (primitive->rank() > rank())
		return primitive->evaluate_(value, true, primitive->promote_(primitiveLeft), exception, expr);

	return primitiveLeft->evaluate_(value, false, primitiveLeft->promote_(primitive), exception, expr);
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::prepForExpression_(){
	return shared_from_this();
}
