#pragma once

#ifndef STRUCTURED_SCRIPT_CLASS_H
#define STRUCTURED_SCRIPT_CLASS_H

#include "../../Common/ExceptionManagerQuery.h"
#include "../../Common/TypeQuery.h"
#include "../../Common/ObjectQuery.h"
#include "../../Common/Factory.h"

#include "../../Interfaces/Types/IClass.h"
#include "../../Objects/Object.h"

#include "Type.h"

namespace StructuredScript{
	class Class : public Type, public IClass{
	public:
		typedef std::list<INode::Ptr> FieldListType;

		Class(IStorage *storage, const ParentListType &parents, const std::string &name)
			: Type(storage, parents, name){}

		virtual IAny::Ptr create(IStorage *storage, IExceptionManager *exception, INode *expr) override;

		virtual IMemory::Ptr constructor() override;

		virtual IMemory::Ptr destructor() override;

		void setFieldList(const FieldListType &fields);

	private:
		FieldListType fields_;
	};
}

#endif /* !STRUCTURED_SCRIPT_CLASS_H */