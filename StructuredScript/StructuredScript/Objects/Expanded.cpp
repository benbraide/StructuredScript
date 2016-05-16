#include "Expanded.h"

void StructuredScript::Objects::Expanded::expand(IFunction::ArgListType &args){
	auto expansion = dynamic_cast<IExpansion *>(expansion_.get());
	if (expansion != nullptr)
		expansion->expand(args);
}
