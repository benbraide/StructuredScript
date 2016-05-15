#pragma once

#ifndef STRUCTURED_SCRIPT_COMPOUND_TYPE_INTERFACE_H
#define STRUCTURED_SCRIPT_COMPOUND_TYPE_INTERFACE_H

#include "../IType.h"

namespace StructuredScript{
	namespace Interfaces{
		class CompoundType{
		public:
			virtual ~CompoundType(){}

			virtual std::shared_ptr<Memory> findMemberMemory(const std::string &name, unsigned short searchScope = Storage::SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Memory> findMemberFunctionMemory(const std::string &name, unsigned short searchScope = Storage::SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Memory> findMemberOperatorMemory(const std::string &name, unsigned short searchScope = Storage::SEARCH_DEFAULT) = 0;

			virtual std::shared_ptr<Memory> findMemberTypenameOperatorMemory(const std::string &name, unsigned short searchScope = Storage::SEARCH_DEFAULT) = 0;
		};
	}

	typedef Interfaces::CompoundType ICompoundType;
}

#endif /* !STRUCTURED_SCRIPT_COMPOUND_TYPE_INTERFACE_H */