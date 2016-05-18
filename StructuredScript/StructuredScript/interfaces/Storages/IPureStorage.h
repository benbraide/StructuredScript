#pragma once

#ifndef STRUCTURED_SCRIPT_PURE_STORAGE_INTERFACE_H
#define STRUCTURED_SCRIPT_PURE_STORAGE_INTERFACE_H

#include "../IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class PureStorage{
		public:
			virtual ~PureStorage(){}

			virtual bool use(Storage *storage) = 0;

			virtual bool use(const std::string &name, Type::Ptr value) = 0;

			virtual bool use(const std::string &name, Memory::Ptr value) = 0;

			virtual bool useOperator(const std::string &name, Memory::Ptr value) = 0;

			virtual bool useTypenameOperator(Type::Ptr name, Memory::Ptr value) = 0;
		};
	}

	typedef Interfaces::PureStorage IPureStorage;
}

#endif /* !STRUCTURED_SCRIPT_PURE_STORAGE_INTERFACE_H */