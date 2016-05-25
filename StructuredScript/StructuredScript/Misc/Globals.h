#pragma once

#ifndef STRUCTURED_SCRIPT_GLOBAL_MISCELLANEOUS_H
#define STRUCTURED_SCRIPT_GLOBAL_MISCELLANEOUS_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/Storages/IGlobalStorage.h"

#include "../Scanner/Wells/FileCharacterWell.h"
#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"

namespace StructuredScript{
	class Globals{
	public:
		typedef std::list<std::string> PathListType;

		static void init();

		static void path(const std::string &path);

	private:
		static IAny::Ptr require_(const std::string &path, IStorage *storage, IExceptionManager *exception, INode *expr);

		static std::string path_;
		static PathListType paths_;
	};
}

#endif /* !STRUCTURED_SCRIPT_GLOBAL_MISCELLANEOUS_H */