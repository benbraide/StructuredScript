#pragma once

#ifndef STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_INTERFACE_H
#define STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_INTERFACE_H

#include "../IExceptionManager.h"

namespace StructuredScript{
	namespace Interfaces{
		class PrimitiveObject{
		public:
			virtual ~PrimitiveObject(){}

			virtual Any::Ptr evaluateLeftUnary(const std::string &value, ExceptionManager *exception, Node *expr) = 0;

			virtual Any::Ptr evaluateRightUnary(const std::string &value, ExceptionManager *exception, Node *expr) = 0;

			virtual Any::Ptr evaluateBinary(const std::string &value, Any::Ptr right, ExceptionManager *exception, Node *expr) = 0;

			virtual int rank() = 0;
		};

		class Void{
		public:
			virtual ~Void(){}
		};

		class Bool{
		public:
			virtual ~Bool(){}
		};

		class Bit{
		public:
			virtual ~Bit(){}
		};

		class Byte{
		public:
			virtual ~Byte(){}
		};

		class NaN{
		public:
			virtual ~NaN(){}
		};

		class Number{
		public:
			virtual ~Number(){}
		};

		class Integer{
		public:
			virtual ~Integer(){}
		};

		class SignedInteger{
		public:
			virtual ~SignedInteger(){}
		};

		class Real{
		public:
			virtual ~Real(){}
		};

		class String{
		public:
			virtual ~String(){}
		};

		class TypeObject{
		public:
			virtual ~TypeObject(){}

			virtual Type::Ptr value() = 0;
		};

		class IndexObject{
		public:
			virtual ~IndexObject(){}
		};

		class IndexTarget{
		public:
			virtual ~IndexTarget(){}

			virtual Any::Ptr getIndexValue(unsigned int index) = 0;
		};
	}

	typedef Interfaces::PrimitiveObject	IPrimitiveObject;
	typedef Interfaces::Void			IVoid;
	typedef Interfaces::Bool			IBool;
	typedef Interfaces::Bit				IBit;
	typedef Interfaces::Byte			IByte;
	typedef Interfaces::NaN				INaN;
	typedef Interfaces::Number			INumber;
	typedef Interfaces::Integer			IInteger;
	typedef Interfaces::SignedInteger	ISignedInteger;
	typedef Interfaces::Real			IReal;
	typedef Interfaces::String			IString;
	typedef Interfaces::TypeObject		ITypeObject;
	typedef Interfaces::IndexObject		IIndexObject;
	typedef Interfaces::IndexTarget		IIndexTarget;
}

#endif /* !STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_INTERFACE_H */