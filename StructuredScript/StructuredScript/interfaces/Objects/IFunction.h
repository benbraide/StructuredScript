#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_INTERFACE_H
#define STRUCTURED_SCRIPT_FUNCTION_INTERFACE_H

#include <list>

#include "../IExceptionManager.h"

namespace StructuredScript{
	namespace Interfaces{
		class Function{
		public:
			typedef Storage::ArgListType	ArgListType;
			typedef std::list<IType::Ptr>	TypeListType;

			virtual ~Function(){}

			virtual bool init(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual bool accepts(int count) = 0;

			virtual int score(const ArgListType &args) = 0;

			virtual int score(const TypeListType &args) = 0;

			virtual IAny::Ptr call(const ArgListType &args, Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};
	}

	typedef Interfaces::Function IFunction;
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_INTERFACE_H */