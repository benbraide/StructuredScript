#pragma once

#ifndef STRUCTURED_SCRIPT_PRIMITIVE_TYPE_H
#define STRUCTURED_SCRIPT_PRIMITIVE_TYPE_H

#include "Query.h"

namespace StructuredScript{
	class PrimitiveType : public IType, public IPrimitiveType{
	public:
		PrimitiveType(const std::string &name, Typename value)
			: name_(name), value_(value){}

		virtual Ptr ptr() override;

		virtual IStorage *storage() override;

		virtual bool isEqual(const IType &target) const override;

		virtual bool isParent(const IType &target) const override;

		virtual bool isCompatibleWith(const IType &target) const override;

		virtual Ptr getCompatibleType(const IType &target) override;

		virtual std::string name() const override;

		virtual Typename value() const override;

		virtual bool has(Typename value) const override;

		virtual bool has(Typename from, Typename to) const override;

	private:
		std::string name_;
		Typename value_;
	};

	class AnyType : public PrimitiveType, public IAnyType{
	public:
		AnyType()
			: PrimitiveType("any", Typename::TYPE_NAME_ANY){}
	};
}

#endif /* !STRUCTURED_SCRIPT_PRIMITIVE_TYPE_H */