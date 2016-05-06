#pragma once

#ifndef STRUCTURED_SCRIPT_COMPOSITE_TYPE_H
#define STRUCTURED_SCRIPT_COMPOSITE_TYPE_H

#include "Query.h"

namespace StructuredScript{
	class CompositeType : public IType{
	public:
		typedef std::list<Ptr> ListType;

		CompositeType(const ListType &types)
			: types_(types){}

		virtual Ptr ptr() override;

		virtual IStorage *storage() override;

		virtual bool isEqual(const IType &target) const override;

		virtual bool isParent(const IType &target) const override;

		virtual bool isCompatibleWith(const IType &target) const override;

		virtual Ptr getCompatibleType(const IType &target) override;

		virtual std::string name() const override;

	protected:
		ListType types_;
	};
}

#endif /* !STRUCTURED_SCRIPT_COMPOSITE_TYPE_H */