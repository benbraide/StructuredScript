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
			IStorage::ExternalCallType getExternalCall_(IStorage *storage, IExceptionManager *exception, INode *expr);

			Ptr getReturnValue_(IExceptionManager *exception, INode *expr);

			virtual void initialize(IObject *object, IStorage *storage, IExceptionManager *exception, INode *expr);

			INode::Ptr definition_;
		};

		class Constructor : public Function, public IConstructor{
		public:
			typedef std::map<std::string, INode::Ptr> InitializerListType;

			Constructor(INode::Ptr parameters, INode::Ptr definition, const InitializerListType &initializers)
				: Function(nullptr, parameters, definition), initializers_(initializers){}

			virtual Ptr call(bool rightUnary, IAny::Ptr object, const ArgListType &args, IExceptionManager *exception, INode *expr) override;

			virtual void initialize(IObject *object, IStorage *storage, IExceptionManager *exception, INode *expr) override;

		private:
			void initializeParent_(const std::pair<std::string, INode::Ptr> &info, IObject *object, IStorage *storage, IExceptionManager *exception, INode *expr);

			InitializerListType initializers_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_H */