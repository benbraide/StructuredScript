#pragma once

#ifndef STRUCTURED_SCRIPT_QUERY_H
#define STRUCTURED_SCRIPT_QUERY_H

#include <list>
#include <memory>

#include "../Interfaces/IMemory.h"
#include "../Interfaces/IStorage.h"
#include "../Interfaces/Storages/IFunctionMemory.h"

#include "../Interfaces/IAny.h"
#include "../Interfaces/Objects/IPrimitiveObject.h"

#include "../Interfaces/INode.h"

#include "../Interfaces/IType.h"
#include "../Interfaces/Types/IPrimitiveType.h"

#include "../Interfaces/IExceptionManager.h"

namespace StructuredScript{
	namespace Query{
		class ExceptionManager{
		public:
			static void clear(IExceptionManager *xManager);

			static void set(IExceptionManager *xManager, IAny::Ptr exception);

			static void setOnce(IExceptionManager *xManager);

			static void setExit(IExceptionManager *xManager);

			static void setReturn(IExceptionManager *xManager);

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

		class Type{
		public:
			static bool isAny(const IType *type);
		};
	}

	/*template <class Type>
	class Query{
	public:
		typedef std::shared_ptr<Type>	Ptr;
		typedef std::list<Ptr>			ListType;

		static bool isAnyType(const Type *target){
			return false;
		}

		static bool isCompositeType(const Type *target){
			return false;
		}

		static bool isEmpty(const Type *target){
			return false;
		}

		static bool isOperator(const Type *target){
			return false;
		}

		static bool isLeftUnary(const Type *target){
			return false;
		}

		static bool isRightUnary(const Type *target){
			return false;
		}

		static bool isBinary(const Type *target){
			return false;
		}

		static Ptr getOperand(const Type *target){
			return nullptr;
		}

		static Ptr getLeftOperand(const Type *target){
			return nullptr;
		}

		static Ptr getRightOperand(const Type *target){
			return nullptr;
		}

		static void split(const Type *target, ListType &list, bool asBinary = false){}

		static bool isTemplated(const Type *target){
			return false;
		}

		static IFunctionMemory *toFunctionMemory(Type *target){
			return nullptr;
		}
	};*/
}

#endif /* !STRUCTURED_SCRIPT_QUERY_H */