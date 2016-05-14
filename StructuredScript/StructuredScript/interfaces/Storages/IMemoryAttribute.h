#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_ATTRIBUTE_INTERFACE_H
#define STRUCTURED_SCRIPT_MEMORY_ATTRIBUTE_INTERFACE_H

#include "../IExceptionManager.h"

namespace StructuredScript{
	namespace Interfaces{
		class Memory;

		class MemoryAttribute : protected std::enable_shared_from_this<MemoryAttribute>{
		public:
			typedef std::shared_ptr<MemoryAttribute> Ptr;

			virtual ~MemoryAttribute(){}

			virtual Ptr ptr() = 0;

			virtual bool appliesTo(std::shared_ptr<Memory> memory, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual bool appliesTo(std::shared_ptr<Node> node, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual void apply(std::shared_ptr<Memory> memory, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual void apply(std::shared_ptr<Node> node, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Ptr spawn(std::shared_ptr<Node> args, Storage *storage, ExceptionManager *exception, Node *expr) = 0;

			virtual Ptr find(const std::string &name, Storage *storage, ExceptionManager *exception, Node *expr) = 0;
		};

		class ParameterizedAttribute{
		public:
			virtual ~ParameterizedAttribute(){}

			virtual MemoryAttribute::Ptr value() = 0;

			virtual std::shared_ptr<Node> arg() = 0;
		};
	}

	typedef Interfaces::MemoryAttribute			IMemoryAttribute;
	typedef Interfaces::ParameterizedAttribute	IParameterizedAttribute;
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_ATTRIBUTE_INTERFACE_H */