#pragma once

#ifndef STRUCTURED_SCRIPT_EXCEPTION_MANAGER_QUERY_H
#define STRUCTURED_SCRIPT_EXCEPTION_MANAGER_QUERY_H

#include "../Interfaces/INode.h"
#include "../Interfaces/IExceptionManager.h"

namespace StructuredScript{
	namespace Query{
		class ExceptionManager{
		public:
			static void clear(IExceptionManager *xManager);

			static void set(IExceptionManager *xManager, IAny::Ptr exception);

			static IAny::Ptr setAndReturnObject(IExceptionManager *xManager, IAny::Ptr exception);

			static INode::Ptr setAndReturnNode(IExceptionManager *xManager, IAny::Ptr exception);

			static std::string combine(const std::string &exception, INode *expr);

			static void setOnce(IExceptionManager *xManager);

			static void setExit(IExceptionManager *xManager, IAny::Ptr value);

			static void setReturn(IExceptionManager *xManager, IAny::Ptr value);

			static void setBreak(IExceptionManager *xManager);

			static void setContinue(IExceptionManager *xManager);

			static IAny::Ptr get(IExceptionManager *xManager);

			static bool has(IExceptionManager *xManager);

			static bool hasOnce(IExceptionManager *xManager);

			static bool hasExit(IExceptionManager *xManager);

			static bool hasReturn(IExceptionManager *xManager);

			static bool hasBreak(IExceptionManager *xManager);

			static bool hasContinue(IExceptionManager *xManager);
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_EXCEPTION_MANAGER_QUERY_H */