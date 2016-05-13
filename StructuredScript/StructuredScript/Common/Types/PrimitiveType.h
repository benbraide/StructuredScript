#pragma once

#ifndef STRUCTURED_SCRIPT_PRIMITIVE_TYPE_H
#define STRUCTURED_SCRIPT_PRIMITIVE_TYPE_H

#include "../TypeQuery.h"
#include "../../Storage/MemoryState.h"
#include "../../Interfaces/Storages/IGlobalStorage.h"

namespace StructuredScript{
	class PrimitiveType : public IType, public IPrimitiveType{
	public:
		PrimitiveType(const std::string &name, Typename value)
			: name_(name), value_(value){}

		virtual Ptr ptr() override;

		virtual Ptr base() override;

		virtual IStorage *storage() override;

		virtual bool isAny() override;

		virtual bool isEqual(Ptr target) override;

		virtual bool isParent(Ptr target) override;

		virtual bool isCompatibleWith(Ptr target, bool family = false) override;

		virtual Ptr getCompatibleType(Ptr target, bool family = false) override;

		virtual std::string name() const override;

		virtual Typename value() const override;

	private:
		std::string name_;
		Typename value_;
	};

	class AnyType : public PrimitiveType, public IAnyType{
	public:
		AnyType()
			: PrimitiveType("any", Typename::TYPE_NAME_ANY){}

		virtual bool isAny() override;
	};
}

#endif /* !STRUCTURED_SCRIPT_PRIMITIVE_TYPE_H */