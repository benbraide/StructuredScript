#pragma once

#ifndef STRUCTURED_SCRIPT_UNDEFINED_OBJECT_H
#define STRUCTURED_SCRIPT_UNDEFINED_OBJECT_H

#include "Primitive.h"

namespace StructuredScript{
	namespace Objects{
		class Undefined : public Primitive, public IUndefined{
		public:
			Undefined()
				: Primitive(nullptr){}

			virtual IType::Ptr type() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_UNDEFINED_OBJECT_H */