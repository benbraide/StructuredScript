#pragma once

#ifndef STRUCTURED_SCRIPT_COMPOSITE_PRIMITIVE_TYPE_H
#define STRUCTURED_SCRIPT_COMPOSITE_PRIMITIVE_TYPE_H

#include "CompositeType.h"

namespace StructuredScript{
	class CompositePrimitiveType : public CompositeType, public IPrimitiveType, public ICompositePrimitiveType{
	public:
		CompositePrimitiveType(const ListType &types, const std::string &name)
			: CompositeType(types), name_(name){}

		virtual bool isParent(Ptr target) override;

		virtual std::string name() const override;

		virtual Typename value() const override;

	private:
		std::string name_;
	};
}

#endif /* !STRUCTURED_SCRIPT_COMPOSITE_PRIMITIVE_TYPE_H */