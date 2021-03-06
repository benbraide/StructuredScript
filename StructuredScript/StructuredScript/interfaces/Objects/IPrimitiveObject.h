#pragma once

#ifndef STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_INTERFACE_H
#define STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_INTERFACE_H

#include "IFunction.h"

namespace StructuredScript{
	namespace Interfaces{
		class ArrayObject;

		class PrimitiveObject{
		public:
			virtual ~PrimitiveObject(){}

			virtual int rank() = 0;
		};

		class Enum{
		public:
			virtual ~Enum(){}

			virtual std::string name() const = 0;
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

			virtual unsigned int size() const = 0;
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

		class Undefined{
		public:
			virtual ~Undefined(){}
		};

		class Expansion{
		public:
			virtual ~Expansion(){}

			virtual void expand(Function::ArgListType &args) = 0;

			virtual std::shared_ptr<Memory> add() = 0;
		};

		class Expanded{
		public:
			virtual ~Expanded(){}

			virtual void expand(Function::ArgListType &args) = 0;
		};

		class Property{
		public:
			virtual ~Property(){}

			virtual Any::Ptr propertyClone(Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Type::Ptr propertyType() = 0;

			virtual void setOwner(Any::Ptr owner) = 0;
		};

		class Range{
		public:
			virtual ~Range(){}

			virtual void extend(ArrayObject &object, unsigned int index, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual std::string str() = 0;
		};

		class NodeObject{
		public:
			virtual ~NodeObject(){}

			virtual Node::Ptr value() = 0;
		};

		class MemoryObject{
		public:
			virtual ~MemoryObject(){}

			virtual Memory::Ptr value() = 0;
		};

		class StorageObject{
		public:
			virtual ~StorageObject(){}

			virtual Storage *value() = 0;
		};
	}

	typedef Interfaces::PrimitiveObject	IPrimitiveObject;
	typedef Interfaces::Enum			IEnum;
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
	typedef Interfaces::Undefined		IUndefined;
	typedef Interfaces::Expansion		IExpansion;
	typedef Interfaces::Expanded		IExpanded;
	typedef Interfaces::Property		IProperty;
	typedef Interfaces::Range			IRange;
	typedef Interfaces::NodeObject		INodeObject;
	typedef Interfaces::MemoryObject	IMemoryObject;
	typedef Interfaces::StorageObject	IStorageObject;
}

#endif /* !STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_INTERFACE_H */