#include "Memory.h"

StructuredScript::Storage::Memory::Memory(IStorage *storage, IType::Ptr type, IAny::Ptr value, IMemoryAttributes::Ptr attributes)
	: storage_(storage), type_(type), value_(value), attributes_(attributes){
	if (value_ != nullptr)
		value_->setMemory(this);
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::Memory::ptr(){
	return shared_from_this();
}

void StructuredScript::Storage::Memory::assign(IAny::Ptr object, IStorage *storage, IExceptionManager *exception, INode *expr){
	if (attributes_ != nullptr){//Validate access
		if (value_ != nullptr && !Query::Object::isUndefined(value_) && (attributes_->hasAttribute(""))){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"Cannot modify object!", expr)));

			return;
		}
	}

	auto declaredType = dynamic_cast<IDeclaredType *>(type_.get());
	if (declaredType != nullptr && value_ != nullptr && !Query::Object::isUndefined(value_)){//Validate access
		auto states = MemoryState(declaredType->states());
		if (states.isConstant() || states.isFinal()){//Cannot assign to a const | final memory
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"Cannot modify memory!", expr)));

			return;
		}
	}

	auto type = object->type();
	if (type == nullptr){//Expected type
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Expected type of object during assignment!", expr)));

		return;
	}

	if (type_ != nullptr){//Validate assignment
		auto compatibleType = type_->getCompatibleType(type);
		if (compatibleType == nullptr){//Incompatible types -- use type as is
			if (declaredType != nullptr){//Compatible type required
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
					"Incompatible types!", expr)));

				return;
			}
			
			compatibleType = type_;
		}

		if (declaredType != nullptr){//Get reference

		}
		else{//Cast object to compatible type
			object = object->cast(compatibleType->base(), storage, exception, expr);
			if (Query::ExceptionManager::has(exception))
				return;

			if (object == nullptr){//Failed to do conversion
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
					"Incompatible types!", expr)));

				return;
			}
		}

		if (object->memory() != nullptr)//Create object copy
			object = object->clone(storage, exception, expr);

		if (Query::ExceptionManager::has(exception))
			return;
	}

	if (value_ != nullptr)//Unbind previous
		value_->setMemory(nullptr);

	(value_ = object)->setMemory(this);
}

StructuredScript::IAny::Ptr StructuredScript::Storage::Memory::object(){
	return value_;
}

StructuredScript::Interfaces::Type::Ptr StructuredScript::Storage::Memory::type(){
	return type_;
}

StructuredScript::Interfaces::MemoryAttributes::Ptr StructuredScript::Storage::Memory::attributes(){
	return attributes_;
}

StructuredScript::IStorage *StructuredScript::Storage::Memory::storage(){
	return storage_;
}
