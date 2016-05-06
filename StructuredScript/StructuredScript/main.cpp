#include "CppUnitLite/TestHarness.h"

#include "Storage/GlobalStorage.h"
#include "Objects/Integer.h"
#include "Objects/Real.h"

StructuredScript::IGlobalStorage *StructuredScript::IGlobalStorage::globalStorage;

int main(){
	TestResult tr;
	TestRegistry::runAllTests(tr);

	StructuredScript::Storage::GlobalStorage globalStorage;
	StructuredScript::IGlobalStorage::globalStorage = &globalStorage;

	globalStorage.init();

	auto s = std::make_shared<StructuredScript::Objects::Short>(9);
	auto i = std::make_shared<StructuredScript::Objects::LDouble>(18.512345678901234567890);

	auto r = s->evaluateBinary("-", i, nullptr, nullptr);
	auto rc = r->clone(nullptr, nullptr, nullptr);
	auto ra = r->cast(globalStorage.getPrimitiveType(StructuredScript::Typename::TYPE_NAME_INT), nullptr, nullptr, nullptr);
	auto rb = ra->cast(globalStorage.getPrimitiveType(StructuredScript::Typename::TYPE_NAME_LDOUBLE), nullptr, nullptr, nullptr);
	auto sb = s->evaluateBinary(">", i, nullptr, nullptr);

	auto ss = s->str(nullptr, nullptr, nullptr);
	auto is = i->str(nullptr, nullptr, nullptr);
	auto rs = r->str(nullptr, nullptr, nullptr);
	auto rcs = rc->str(nullptr, nullptr, nullptr);
	auto ras = ra->str(nullptr, nullptr, nullptr);
	auto rbs = rb->str(nullptr, nullptr, nullptr);
	auto sbs = sb->str(nullptr, nullptr, nullptr);

	return 0;
}