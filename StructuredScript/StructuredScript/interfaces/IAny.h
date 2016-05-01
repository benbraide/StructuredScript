#pragma once

#ifndef STRUCTURED_SCRIPT_ANY_INTERFACE_H
#define STRUCTURED_SCRIPT_ANY_INTERFACE_H

#include <memory>

#include "IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class Node;
		class Memory;
		class ExceptionManage;

		class Any : protected std::enable_shared_from_this<Any>{
		public:
			typedef std::shared_ptr<Any> Ptr;

			virtual ~Any(){}

			virtual Ptr ptr() = 0;

			virtual Ptr clone(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual void setMemory(Memory *memory) = 0;

			virtual Memory *getMemory() = 0;

			virtual Type *getType() = 0;

			virtual std::string str(Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};
	}

	typedef Interfaces::Any IAny;
}

#endif /* !STRUCTURED_SCRIPT_ANY_INTERFACE_H */