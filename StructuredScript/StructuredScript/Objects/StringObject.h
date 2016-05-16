#pragma once

#ifndef STRUCTURED_SCRIPT_STRING_OBJECT_H
#define STRUCTURED_SCRIPT_STRING_OBJECT_H

#include "Real.h"

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Types/Type.h"
#include "../Common/Factory.h"

#include "../Interfaces/Storages/IGlobalStorage.h"
#include "../Interfaces/IParser.h"
#include "../Interfaces/IScanner.h"
#include "../Scanner/Wells/StringCharacterWell.h"

namespace StructuredScript{
	namespace Objects{
		class String : public TypedPrimitive<std::string, Primitive::STRING_RANK>, public IStorage, public IString{
		public:
			String(const std::string &value)
				: TypedPrimitive(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_STRING), value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual IStorage *parent() override;

			virtual std::shared_ptr<IStorage> *addStorage(const std::string &name) override;

			virtual IStorage *findStorage(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IType::Ptr *addType(const std::string &name) override;

			virtual IType::Ptr findType(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addMemory(const std::string &name) override;

			virtual IMemory::Ptr findMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr findFunctionMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemory::Ptr *addTypenameOperatorMemory(const std::string &name) override;

			virtual IMemory::Ptr findTypenameOperatorMemory(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IMemoryAttribute::Ptr *addMemoryAttribute(const std::string &name) override;

			virtual IMemoryAttribute::Ptr findMemoryAttribute(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual ExternalCallType findExternalCall(const std::string &name) override;

			virtual bool remove(IMemory::Ptr target) override;

			static void init(std::shared_ptr<Type> type, IScanner &scanner, IParser &parser);

		protected:
			virtual IAny::Ptr promote_(Primitive *target) override{
				switch (target->rank()){
				case Primitive::CHAR_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::CHAR_RANK>::type *>(target)->value()));
				case Primitive::UCHAR_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::UCHAR_RANK>::type *>(target)->value()));
				case Primitive::SHORT_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::SHORT_RANK>::type *>(target)->value()));
				case Primitive::USHORT_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::USHORT_RANK>::type *>(target)->value()));
				case Primitive::INT_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::INT_RANK>::type *>(target)->value()));
				case Primitive::UINT_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::UINT_RANK>::type *>(target)->value()));
				case Primitive::LONG_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::LONG_RANK>::type *>(target)->value()));
				case Primitive::ULONG_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::ULONG_RANK>::type *>(target)->value()));
				case Primitive::LLONG_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::LLONG_RANK>::type *>(target)->value()));
				case Primitive::ULLONG_RANK:
					return std::make_shared<String>(std::to_string(dynamic_cast<PrimitiveType<Primitive::ULLONG_RANK>::type *>(target)->value()));
				case Primitive::FLOAT_RANK:
					return std::make_shared<String>(Float::toString(dynamic_cast<PrimitiveType<Primitive::FLOAT_RANK>::type *>(target)->value()));
				case Primitive::DOUBLE_RANK:
					return std::make_shared<String>(Double::toString(dynamic_cast<PrimitiveType<Primitive::DOUBLE_RANK>::type *>(target)->value()));
				case Primitive::LDOUBLE_RANK:
					return std::make_shared<String>(LDouble::toString(dynamic_cast<PrimitiveType<Primitive::LDOUBLE_RANK>::type *>(target)->value()));
				default:
					break;
				}

				return nullptr;
			}

			virtual IAny::Ptr evaluate_(const std::string &value, TypedPrimitive *left, TypedPrimitive *right, IExceptionManager *exception, INode *expr) override{
				auto leftBase = left->base(), rightBase = right->base();
				if (value == "+")
					return std::make_shared<String>(dynamic_cast<String *>(leftBase.get())->value_ + dynamic_cast<String *>(rightBase.get())->value_);

				return TypedPrimitive::evaluate_(value, left, right, exception, expr);
			}
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STRING_OBJECT_H */