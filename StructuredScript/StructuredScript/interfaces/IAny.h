#pragma once

#ifndef STRUCTURED_SCRIPT_ANY_INTERFACE_H
#define STRUCTURED_SCRIPT_ANY_INTERFACE_H

#include <memory>

#include "IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class ExceptionManager;

		class Any : protected std::enable_shared_from_this<Any>{
		public:
			typedef std::shared_ptr<Any> Ptr;

			virtual ~Any(){}

			virtual Ptr ptr() = 0;

			virtual Ptr clone(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Ptr cast(Type::Ptr type, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Ptr base() = 0;

			virtual Ptr assign(const std::string &value, Ptr right, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Ptr evaluateLeftUnary(const std::string &value, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Ptr evaluateRightUnary(const std::string &value, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Type::Ptr type() = 0;

			virtual void setMemory(Memory *memory) = 0;

			virtual Memory *memory() = 0;

			virtual bool truth(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual std::string str(Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};
	}

	typedef Interfaces::Any IAny;
}

#endif /* !STRUCTURED_SCRIPT_ANY_INTERFACE_H */