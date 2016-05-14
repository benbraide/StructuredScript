#pragma once

#ifndef STRUCTURED_SCRIPT_EXPANSION_OBJECT_H
#define STRUCTURED_SCRIPT_EXPANSION_OBJECT_H

#include <list>

#include "Primitive.h"
#include "../Storage/Memory.h"

namespace StructuredScript{
	namespace Objects{
		class Expansion : public Primitive, public IExpansion{
		public:
			typedef std::list<IMemory::Ptr> MemoryListType;

			Expansion(IType::Ptr type)
				: Primitive(type){}

			virtual void expand(IFunction::ArgListType &args) override;

			virtual IMemory::Ptr add() override;

		private:
			MemoryListType entries_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_EXPANSION_OBJECT_H */