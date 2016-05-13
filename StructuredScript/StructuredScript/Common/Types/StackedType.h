#pragma once

#ifndef STRUCTURED_SCRIPT_STACKED_TYPE_H
#define STRUCTURED_SCRIPT_STACKED_TYPE_H

#include "../TypeQuery.h"

namespace StructuredScript{
	class StackedType : public IType, public IStackedType{
	public:
		explicit StackedType(IType::Ptr value)
			: value_(value){}

		virtual Ptr ptr() override;

		virtual Ptr base() override;

		virtual IStorage *storage() override;

		virtual bool isAny() override;

		virtual bool isParent(Ptr target) override;

		virtual bool isCompatibleWith(Ptr target, bool family = false) override;

		virtual Ptr getCompatibleType(Ptr target, bool family = false) override;

		virtual Ptr value() override;

	protected:
		Ptr value_;
	};

	class ExpandedType : public StackedType, public IExpandedType{
	public:
		explicit ExpandedType(IType::Ptr value)
			: StackedType(value){}

		virtual bool isEqual(Ptr target) override;

		virtual std::string name() const override;
	};
}

#endif /* !STRUCTURED_SCRIPT_STACKED_TYPE_H */