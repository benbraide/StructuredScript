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

StructuredScript::IAny::Ptr StructuredScript::Objects::Primitive::base(){
	return shared_from_this();
}

StructuredScript::IAny::Ptr StructuredScript::Objects::Primitive::assign(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (memory_ == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Assignment requires an lvalue object!", expr)));
	}

	if (value.size() > 1u){//Compound assignment
		right = evaluateBinary(value.substr(0, value.size() - 1), right, storage, exception, expr);
		if (Query::ExceptionManager::has(exception))
			return nullptr;
	}

	auto memory = memory_;
	memory->assign(right, storage, exception, expr);

	return Query::ExceptionManager::has(exception) ? nullptr : memory->object();
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

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateLeftUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (value == "&"){//Reference
		if (memory_ == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"'" + value + "': Requires an lvalue operand!", expr)));
		}

		return PrimitiveFactory::createReference(memory_->ptr());
	}

	if (value == "*")//Copy
		return clone(storage, exception, expr);

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateRightUnary(const std::string &value, IStorage *storage, IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluateBinary(const std::string &value, Ptr right, IStorage *storage,
	IExceptionManager *exception, INode *expr){
	auto rightBase = right->base();
	auto primitive = dynamic_cast<Primitive *>(rightBase.get());
	if (primitive == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"'" + value + "': Operands mismatch!", expr)));
	}

	auto left = prepForExpression_()->base();
	auto primitiveLeft = dynamic_cast<Primitive *>(left.get());

	if (primitive->rank() > rank())
		return primitive->evaluate_(value, true, primitive->promote_(primitiveLeft), exception, expr);

	if (primitive->rank() < rank())
		return primitiveLeft->evaluate_(value, false, primitiveLeft->promote_(primitive), exception, expr);

	return primitiveLeft->evaluate_(value, false, rightBase, exception, expr);
}

int StructuredScript::Objects::Primitive::rank(){
	return -1;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::promote_(Primitive *target){
	return (rank() == target->rank()) ? target->ptr() : nullptr;
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::evaluate_(const std::string &value, bool reversed, Ptr right,
	IExceptionManager *exception, INode *expr){
	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
		"'" + value + "': Operands mismatch!", expr)));
}

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Primitive::prepForExpression_(){
	return shared_from_this();
}
