#include "Void.h"

StructuredScript::Interfaces::Any::Ptr StructuredScript::Objects::Void::clone(IStorage *storage, IExceptionManager *exception, INode *expr){
	return std::make_shared<Void>();
}
