#include "SizeOfNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::SizeOfNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::SizeOfNode::clone(){
	return std::make_shared<SizeOfNode>(value_->clone());
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::SizeOfNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto value = value_->evaluate(storage, exception, expr);
	if (Query::ExceptionManager::has(exception))
		return nullptr;

	value = value->base();
	auto typeObject = dynamic_cast<ITypeObject *>(value.get());
	if (typeObject != nullptr){
		auto type = dynamic_cast<IPrimitiveType *>(typeObject->value().get());
		if (type == nullptr){
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
				Query::ExceptionManager::combine("'sizeof': Can only be applied to primitive numeric types!", expr)));
		}

		switch (type->value()){
		case Typename::TYPE_NAME_CHAR:
		case Typename::TYPE_NAME_UCHAR:
			return PrimitiveFactory::createUInt(sizeof(char));
		case Typename::TYPE_NAME_SHORT:
		case Typename::TYPE_NAME_USHORT:
			return PrimitiveFactory::createUInt(sizeof(short));
		case Typename::TYPE_NAME_INT:
		case Typename::TYPE_NAME_UINT:
			return PrimitiveFactory::createUInt(sizeof(int));
		case Typename::TYPE_NAME_LONG:
		case Typename::TYPE_NAME_ULONG:
			return PrimitiveFactory::createUInt(sizeof(long));
		case Typename::TYPE_NAME_LLONG:
		case Typename::TYPE_NAME_ULLONG:
			return PrimitiveFactory::createUInt(sizeof(long long));
		case Typename::TYPE_NAME_FLOAT:
			return PrimitiveFactory::createUInt(sizeof(float));
		case Typename::TYPE_NAME_DOUBLE:
			return PrimitiveFactory::createUInt(sizeof(double));
		case Typename::TYPE_NAME_LDOUBLE:
			return PrimitiveFactory::createUInt(sizeof(long double));
		default:
			break;
		}

		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'sizeof': Can only be applied to primitive numeric types!", expr)));
	}

	auto number = dynamic_cast<INumber *>(value.get());
	if (number == nullptr){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(
			Query::ExceptionManager::combine("'sizeof': Can only be applied to primitive numeric types!", expr)));
	}

	return PrimitiveFactory::createUInt(number->size());
}

std::string StructuredScript::Nodes::SizeOfNode::str(){
	return ("sizeof " + value_->str());
}

void StructuredScript::Nodes::SizeOfNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::SizeOfNode::attributes(){
	return nullptr;
}
