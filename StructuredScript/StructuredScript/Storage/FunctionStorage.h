#pragma once

#ifndef STRUCTURED_SCRIPT_FUNCTION_STORAGE_H
#define STRUCTURED_SCRIPT_FUNCTION_STORAGE_H

#include "Storage.h"
#include "../Interfaces/Storages/IFunctionStorage.h"

namespace StructuredScript{
	namespace Storage{
		class FunctionStorage : public Storage, public IFunctionStorage{
		public:
			FunctionStorage(IStorage *parent, IAny::Ptr object)
				: Storage(parent), object_(object){}

			virtual IAny *object() override{
				return object_.get();
			}

		private:
			IAny::Ptr object_;
		};

		class RawFunctionStorage : public Storage, public IFunctionStorage{
		public:
			RawFunctionStorage(IStorage *parent, IAny *object)
				: Storage(parent), object_(object){}

			virtual IAny *object() override{
				return object_;
			}

		private:
			IAny *object_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FUNCTION_STORAGE_H */