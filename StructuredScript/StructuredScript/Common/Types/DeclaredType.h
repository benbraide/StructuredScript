#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARED_TYPE_H
#define STRUCTURED_SCRIPT_DECLARED_TYPE_H

#include "../TypeQuery.h"
#include "../../Storage/MemoryState.h"

namespace StructuredScript{
	class DeclaredType : public IType, public IDeclaredType{
	public:
		typedef StructuredScript::Storage::MemoryState MemoryState;

		DeclaredType(IType::Ptr value, const MemoryState &state)
			: value_(value), state_(state){}

		virtual Ptr ptr() override;

		virtual Ptr base() override;

		virtual IStorage *storage() override;

		virtual bool isAny() override;

		virtual bool isEqual(Ptr target) override;

		virtual bool isParent(Ptr target) override;

		virtual bool isCompatibleWith(Ptr target, bool family = false) override;

		virtual Ptr getCompatibleType(Ptr target, bool family = false) override;

		virtual std::string name() const override;

		virtual IType::Ptr value() override;

		virtual void states(unsigned short value) override;

		virtual unsigned short states() const override;

	private:
		bool isEqual_(Ptr target);

		IType::Ptr value_;
		MemoryState state_;
	};
}

#endif /* !STRUCTURED_SCRIPT_DECLARED_TYPE_H */