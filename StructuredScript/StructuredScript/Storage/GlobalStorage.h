#pragma once

#ifndef STRUCTURED_SCRIPT_GLOBAL_STORAGE_H
#define STRUCTURED_SCRIPT_GLOBAL_STORAGE_H

#include "Storage.h"

#include "../Interfaces/Storages/IGlobalStorage.h"
#include "../Objects/Primitive.h"

#include "../Common/Type.h"
#include "../Common/PrimitiveType.h"
#include "../Common/CompositePrimitiveType.h"
#include "../Common/Factory.h"

namespace StructuredScript{
	namespace Storage{
		class GlobalStorage : public Storage, public IGlobalStorage{
		public:
			typedef std::map<Typename, IType::Ptr> ListType;

			GlobalStorage()
				: Storage(nullptr){}

			void init();

			virtual IType::Ptr findType(const std::string &name, bool localOnly) override;

			virtual IType::Ptr getPrimitiveType(Typename type) override;

			virtual IType::Ptr getPrimitiveType(int rank) override;

		private:
			ListType primitives_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_GLOBAL_STORAGE_H */