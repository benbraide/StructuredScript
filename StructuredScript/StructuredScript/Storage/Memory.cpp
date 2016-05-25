#include "Memory.h"

StructuredScript::Storage::Memory::Memory(IStorage::MemoryInfo *info, IStorage *storage, IType::Ptr type, IMemoryAttributes::Ptr attributes)
	: info_(info), storage_(storage), type_(type), attributes_(attributes){}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::Memory::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Memory::Ptr StructuredScript::Storage::Memory::clone(){
	auto memory = std::make_shared<Memory>(nullptr, storage_, type_, attributes_);
	memory->value_ = value_.lock();

	return memory;
}

void StructuredScript::Storage::Memory::assign(IAny::Ptr object, IStorage *storage, IExceptionManager *exception, INode *expr){
	auto value = value_.lock();
	if (attributes_ != nullptr){//Validate access
		if (value != nullptr && !Query::Object::isUndefined(value) && (attributes_->hasAttribute(""))){
			Query::ExceptionManager::set(exception, PrimitiveFactory::createString(Query::ExceptionManager::combine(
				"Cannot modify object!", expr)));

			return;
		}
	}

	auto states = MemoryState(type_->states());
	if ((states.isConstant() || states.isFinal()) && value != nullptr && !Query::Object::isUndefined(value)){//Cannot assign to a const | final memory
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
		else if (!compatibleType->isAny()){//Cast object to compatible type
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

	assign(object);
}

StructuredScript::IAny::Ptr StructuredScript::Storage::Memory::object(){
	return value_.lock();
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

void StructuredScript::Storage::Memory::setStorage(IStorage *storage){
	storage_ = storage;
}

void StructuredScript::Storage::Memory::assign(IAny::Ptr object){
	auto value = value_.lock();
	if (value != nullptr)//Unbind previous
		value->setMemory(nullptr);

	value_ = object;
	if (info_ != nullptr)
		info_->value = object;

	object->setMemory(this);
}
