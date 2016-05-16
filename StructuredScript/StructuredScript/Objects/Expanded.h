#pragma once

#ifndef STRUCTURED_SCRIPT_EXPANDED_OBJECT_H
#define STRUCTURED_SCRIPT_EXPANDED_OBJECT_H

#include "Primitive.h"

namespace StructuredScript{
	namespace Objects{
		class Expanded : public Primitive, public IExpanded{
		public:
			Expanded(Ptr expansion)
				: Primitive(nullptr), expansion_(expansion){}

			virtual void expand(IFunction::ArgListType &args) override;

		private:
			Ptr expansion_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_EXPANDED_OBJECT_H */