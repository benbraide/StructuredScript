#pragma once

#ifndef STRUCTURED_SCRIPT_PARAMETERIZED_ATTRIBUTE_H
#define STRUCTURED_SCRIPT_PARAMETERIZED_ATTRIBUTE_H

#include "../../Common/NodeQuery.h"
#include "../../Interfaces/Storages/IFunctionMemory.h"

namespace StructuredScript{
	namespace Storage{
		class ParameterizedAttribute : public IMemoryAttribute, public IParameterizedAttribute{
		public:
			ParameterizedAttribute(Ptr value, INode::Ptr arg)
				: value_(value), arg_(arg){}

			virtual Ptr ptr() override;

			virtual bool appliesTo(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual bool appliesTo(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void apply(IMemory::Ptr memory, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual void apply(INode::Ptr node, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr spawn(INode::Ptr args, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr find(const std::string &name, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr value() override;

			virtual INode::Ptr arg() override;

		private:
			Ptr value_;
			INode::Ptr arg_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PARAMETERIZED_ATTRIBUTE_H */