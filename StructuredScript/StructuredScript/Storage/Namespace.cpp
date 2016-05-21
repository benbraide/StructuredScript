#include "Namespace.h"

std::string StructuredScript::Storage::Namespace::name() const{
	auto nmspc = dynamic_cast<INamespace *>(parent_);
	return (nmspc == nullptr) ? name_ : (nmspc->name() + "::" + name_);
}
