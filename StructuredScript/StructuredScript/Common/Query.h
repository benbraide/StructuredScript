#pragma once

#ifndef STRUCTURED_SCRIPT_QUERY_H
#define STRUCTURED_SCRIPT_QUERY_H

#include <list>
#include <memory>

#include "../Interfaces/IMemory.h"
#include "../Interfaces/IFunctionMemory.h"
#include "../Interfaces/IStorage.h"

#include "../Interfaces/IAny.h"
#include "../Interfaces/INode.h"

namespace StructuredScript{
	template <class Type>
	class Query{
	public:
		typedef std::shared_ptr<Type>	Ptr;
		typedef std::list<Ptr>			ListType;

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
	};
}

#endif /* !STRUCTURED_SCRIPT_QUERY_H */