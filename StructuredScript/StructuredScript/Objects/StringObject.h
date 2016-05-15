#pragma once

#ifndef STRUCTURED_SCRIPT_STRING_OBJECT_H
#define STRUCTURED_SCRIPT_STRING_OBJECT_H

#include "Any.h"

#include "../Common/Types/Type.h"
#include "../Common/Factory.h"

#include "../Interfaces/Storages/IGlobalStorage.h"
#include "../Interfaces/IParser.h"
#include "../Interfaces/IScanner.h"
#include "../Scanner/Wells/StringCharacterWell.h"

namespace StructuredScript{
	namespace Objects{
		class String : public Any, public IString{
		public:
			String(const std::string &value)
				: Any(IGlobalStorage::globalStorage->getPrimitiveType(Typename::TYPE_NAME_STRING)), value_(value){}

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string &value() override;

			static void init(std::shared_ptr<Type> type, IScanner &scanner, IParser &parser);

		private:
			std::string value_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STRING_OBJECT_H */