#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_INTERFACE_H
#define STRUCTURED_SCRIPT_FUNCTION_INTERFACE_H

#include <list>

#include "../INode.h"
#include "../IExceptionManager.h"

namespace StructuredScript{
	namespace Interfaces{
		class Function{
		public:
			typedef std::list<Any::Ptr>		ArgListType;
			typedef std::list<Type::Ptr>	TypeListType;

			virtual ~Function(){}

			virtual bool init(bool isRightUnary, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual bool isDefined() const = 0;

			virtual bool isStatic() const = 0;

			virtual bool isMember() const = 0;

			virtual bool equals(Any::Ptr target) = 0;

			virtual bool accepts(int count) = 0;

			virtual int score(bool rightUnary, Any::Ptr object, const ArgListType &args) = 0;

			virtual int score(bool rightUnary, Any::Ptr object, const TypeListType &args) = 0;

			virtual Any::Ptr call(bool rightUnary, Any::Ptr object, const ArgListType &args, ExceptionManager *exception, Node *expr) = 0;

			virtual Type::Ptr declaredType() = 0;
		};

		class Constructor{
		public:
			virtual ~Constructor(){}

			virtual void initialize(Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};
	}

	typedef Interfaces::Function	IFunction;
	typedef Interfaces::Constructor	IConstructor;
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_INTERFACE_H */