#pragma once

#ifndef STRUCTURED_SCRIPT_STRING_TYPE_H
#define STRUCTURED_SCRIPT_STRING_TYPE_H

#include "Type.h"
#include "../../Interfaces/Types/IPrimitiveType.h"

namespace StructuredScript{
	class StringType : public Type, public IPrimitiveType{
	public:
		StringType(IStorage *storage)
			: Type(storage, "string"){}

		virtual Typename value() const override;
	};
}

#endif /* !STRUCTURED_SCRIPT_STRING_TYPE_H */