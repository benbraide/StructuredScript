#include "Memory.h"

StructuredScript::Storage::Memory::Memory(IStorage *storage, IType::Ptr type, IAny::Ptr value, IMemoryAttributes::Ptr attributes, bool assignMemory /*= true*/)
	: storage_(storage), type_(type), value_(value), attributes_(attributes){
	if (assignMemory && value_ != nullptr)
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

	auto states = MemoryState(type_->states());
	if ((states.isConstant() || states.isFinal()) && value_ != nullptr && !Query::Object::isUndefined(value_)){//Cannot assign to a const | final memory
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Cannot modify memory!", expr)));

		return;
	}

	object = object->base();
	if (object == nullptr || Query::Object::isUndefined(object) || Query::Object::isExpansion(object) || Query::Object::isExpanded(object)){
		Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
			"Cannot assign an invalid object!", expr)));

		return;
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
			if (states.isReference()){//Compatible type required
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
					"Incompatible types!", expr)));

				return;
			}
			
			compatibleType = type_;
		}

		if (states.isReference()){//Get reference
			auto memory = object->memory();
			if (states.isRValReference()){//Value | Reference
				if (memory != nullptr){
					auto objectType = memory->type();
					auto objectStates = MemoryState((objectType == nullptr) ? MemoryState::STATE_NONE : objectType->states());
					if (!objectStates.isRValReference()){//Only get reference if object is not an rvalue reference
						object = PrimitiveFactory::createReference(memory->ptr());
						dynamic_cast<IDeclaredType *>(type_.get())->states((states -= MemoryState::STATE_RVALUE).states());
					}
				}
			}
			else if (memory == nullptr){//Reference requires an lvalue
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
					"Cannot get reference of an rvalue!", expr)));

				return;
			}
			else//Reference
				object = PrimitiveFactory::createReference(memory->ptr());
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

void StructuredScript::Storage::Memory::assign(IAny::Ptr object){
	if (value_ != nullptr)//Unbind previous
		value_->setMemory(nullptr);

	(value_ = object)->setMemory(this);
}
