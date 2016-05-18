#pragma once

#ifndef STRUCTURED_SCRIPT_ENUM_OBJECT_H
#define STRUCTURED_SCRIPT_ENUM_OBJECT_H

#include "TypedPrimitive.h"

namespace StructuredScript{
	namespace Objects{
		class Enum : public TypedPrimitive<int, -1>, public IEnum {
		public:
			Enum(IType::Ptr type, const std::string &name, int value)
				: TypedPrimitive(type, value), name_(name){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string name() const override;

		private:
			std::string name_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_ENUM_OBJECT_H */