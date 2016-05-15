#pragma once

#ifndef STRUCTURED_SCRIPT_COMPOSITE_TYPE_H
#define STRUCTURED_SCRIPT_COMPOSITE_TYPE_H

#include <list>

#include "../TypeQuery.h"

namespace StructuredScript{
	class CompositeType : public IType, public ICompositeType{
	public:
		typedef std::list<Ptr> ListType;

		CompositeType(const ListType &types)
			: types_(types){}

		virtual Ptr ptr() override;

		virtual Ptr base() override;

		virtual IStorage *storage() override;

		virtual bool isAny() override;

		virtual bool isEqual(Ptr target) override;

		virtual bool isParent(Ptr target) override;

		virtual bool isCompatibleWith(Ptr target, bool family = false) override;

		virtual Ptr getCompatibleType(Ptr target, bool family = false) override;

		virtual std::string name() const override;

		virtual unsigned short states() const override;

		virtual bool isReversedEqual(IType::Ptr target) override;

		virtual bool isReversedParent(IType::Ptr target) override;

		virtual bool isReversedCompatibleWith(IType::Ptr target, bool family = false) override;

		virtual IType::Ptr getReversedCompatibleType(IType::Ptr target, bool family = false) override;

	protected:
		ListType types_;
	};
}

#endif /* !STRUCTURED_SCRIPT_COMPOSITE_TYPE_H */