#pragma once

#ifndef STRUCTURED_SCRIPT_GLOBAL_STORAGE_H
#define STRUCTURED_SCRIPT_GLOBAL_STORAGE_H

#include "Storage.h"
#include "Memory.h"
#include "MemoryAttributes.h"

#include "Attributes/LockedAttribute.h"
#include "Attributes/ConcurrentAttribute.h"
#include "Attributes/OnceAttribute.h"
#include "Attributes/OverrideAttribute.h"
#include "Attributes/AssumeTypeAttribute.h"
#include "Attributes/AssumeConstnessAttribute.h"
#include "Attributes/RightUnaryAttribute.h"
#include "Attributes/CallAttribute.h"

#include "Attributes/ParameterizedAttribute.h"
#include "Attributes/AttributeSpawner.h"

#include "../Interfaces/Storages/IGlobalStorage.h"

#include "../Common/Types/StringType.h"
#include "../Common/Types/PrimitiveType.h"
#include "../Common/Types/CompositePrimitiveType.h"
#include "../Common/Types/DeclaredType.h"
#include "../Common/Factory.h"

#include "../Objects/StringObject.h"
#include "../Objects/FunctionObject.h"
#include "../Objects/NodeObject.h"
#include "../Objects/MemoryObject.h"
#include "../Objects/StorageObject.h"
#include "../Objects/Undefined.h"
#include "../Objects/Array.h"
#include "../Objects/Range.h"

#include "../Misc/Globals.h"

namespace StructuredScript{
	namespace Storage{
		class GlobalStorage : public Storage, public IGlobalStorage{
		public:
			typedef std::map<Typename, IType::Ptr>			ListType;
			typedef std::map<std::string, ExternalCallType>	ExternalCallListType;

			GlobalStorage()
				: Storage(nullptr){}

			void init();

			virtual IType::Ptr findType(const std::string &name, unsigned short searchScope = SEARCH_DEFAULT) override;

			virtual IType::Ptr getPrimitiveType(Typename type) override;

			virtual IType::Ptr getPrimitiveType(int rank) override;

			virtual INode::Ptr parse(const std::string &value) override;

			virtual INode::Ptr parseTerm(const std::string &value) override;

			virtual ExternalCallType findExternalCall(const std::string &name) override;

			virtual void addExternalCall(const std::string &name, ExternalCallType value) override;

			static void path(const std::string &path);

		private:
			ListType primitives_;
			ExternalCallListType externalCalls_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_GLOBAL_STORAGE_H */