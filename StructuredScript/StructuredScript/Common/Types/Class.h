#pragma once

#ifndef STRUCTURED_SCRIPT_CLASS_H
#define STRUCTURED_SCRIPT_CLASS_H

#include "Type.h"

namespace StructuredScript{
	class Class : public Type{
	public:
		typedef std::list<INode::Ptr> FieldListType;

		Class(IStorage *storage, const std::string &name, const FieldListType &fields)
			: Type(storage, name), fields_(fields){}

	private:
		FieldListType fields_;
	};
}

#endif /* !STRUCTURED_SCRIPT_CLASS_H */