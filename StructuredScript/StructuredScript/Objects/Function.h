#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_H
#define STRUCTURED_SCRIPT_FUNCTION_H

#include "FunctionDeclaration.h"

namespace StructuredScript{
	namespace Objects{
		class Function : public FunctionDeclaration{
		public:
			Function(IType::Ptr type, INode::Ptr parameters, INode::Ptr definition)
				: FunctionDeclaration(type, parameters), definition_(definition){}

			virtual bool isDefined() const override;

			virtual Ptr call(bool rightUnary, IAny::Ptr object, const ArgListType &args, IExceptionManager *exception, INode *expr) override;

		protected:
			INode::Ptr definition_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_H */