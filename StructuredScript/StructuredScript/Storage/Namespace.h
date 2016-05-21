#pragma once

#ifndef STRUCTURED_SCRIPT_NAMESPACE_H
#define STRUCTURED_SCRIPT_NAMESPACE_H

#include "Storage.h"
#include "../Interfaces/Storages/INamespace.h"

namespace StructuredScript{
	namespace Storage{
		class Namespace : public Storage, public INamespace{
		public:
			Namespace(IStorage *parent, const std::string &name)
				: Storage(parent), name_(name){}

			virtual std::string name() const override;

		private:
			std::string name_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_NAMESPACE_H */