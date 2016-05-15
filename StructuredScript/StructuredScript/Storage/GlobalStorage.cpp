#include "GlobalStorage.h"

void StructuredScript::Storage::GlobalStorage::init(){
	primitives_.clear();

	auto bit = std::make_shared<Type>(this, "bit");

	primitives_[Typename::TYPE_NAME_BIT]		= bit;

	primitives_[Typename::TYPE_NAME_ANY]		= std::make_shared<AnyType>();
	primitives_[Typename::TYPE_NAME_VOID]		= std::make_shared<PrimitiveType>("void", Typename::TYPE_NAME_VOID);
	primitives_[Typename::TYPE_NAME_BOOLEAN]	= std::make_shared<PrimitiveType>("bool", Typename::TYPE_NAME_BOOLEAN);
	primitives_[Typename::TYPE_NAME_BYTE]		= std::make_shared<PrimitiveType>("byte", Typename::TYPE_NAME_BYTE);
	primitives_[Typename::TYPE_NAME_NAN]		= std::make_shared<PrimitiveType>("NaN", Typename::TYPE_NAME_NAN);
	primitives_[Typename::TYPE_NAME_CHAR]		= std::make_shared<PrimitiveType>("char", Typename::TYPE_NAME_CHAR);
	primitives_[Typename::TYPE_NAME_UCHAR]		= std::make_shared<PrimitiveType>("unsigned char", Typename::TYPE_NAME_UCHAR);
	primitives_[Typename::TYPE_NAME_SHORT]		= std::make_shared<PrimitiveType>("short", Typename::TYPE_NAME_SHORT);
	primitives_[Typename::TYPE_NAME_USHORT]		= std::make_shared<PrimitiveType>("unsigned short", Typename::TYPE_NAME_USHORT);
	primitives_[Typename::TYPE_NAME_INT]		= std::make_shared<PrimitiveType>("int", Typename::TYPE_NAME_INT);
	primitives_[Typename::TYPE_NAME_UINT]		= std::make_shared<PrimitiveType>("unsigned int", Typename::TYPE_NAME_UINT);
	primitives_[Typename::TYPE_NAME_LONG]		= std::make_shared<PrimitiveType>("long", Typename::TYPE_NAME_LONG);
	primitives_[Typename::TYPE_NAME_ULONG]		= std::make_shared<PrimitiveType>("unsigned long", Typename::TYPE_NAME_ULONG);
	primitives_[Typename::TYPE_NAME_LLONG]		= std::make_shared<PrimitiveType>("long long", Typename::TYPE_NAME_LLONG);
	primitives_[Typename::TYPE_NAME_ULLONG]		= std::make_shared<PrimitiveType>("unsigned long long", Typename::TYPE_NAME_ULLONG);
	primitives_[Typename::TYPE_NAME_FLOAT]		= std::make_shared<PrimitiveType>("float", Typename::TYPE_NAME_FLOAT);
	primitives_[Typename::TYPE_NAME_DOUBLE]		= std::make_shared<PrimitiveType>("double", Typename::TYPE_NAME_DOUBLE);
	primitives_[Typename::TYPE_NAME_LDOUBLE]	= std::make_shared<PrimitiveType>("long double", Typename::TYPE_NAME_LDOUBLE);
	primitives_[Typename::TYPE_NAME_STRING]		= std::make_shared<PrimitiveType>("string", Typename::TYPE_NAME_STRING);
	primitives_[Typename::TYPE_NAME_TYPE]		= std::make_shared<PrimitiveType>("type", Typename::TYPE_NAME_TYPE);
	primitives_[Typename::TYPE_NAME_FUNCTION]	= std::make_shared<PrimitiveType>("function_type", Typename::TYPE_NAME_FUNCTION);

	attributes_["Locked"]						= std::make_shared<LockedAttribute>();
	attributes_["Concurrent"]					= std::make_shared<ConcurentAttribute>();
	attributes_["Once"]							= std::make_shared<OnceAttribute>();
	attributes_["Override"]						= std::make_shared<OverrideAttribute>();
	attributes_["AssumeType"]					= std::make_shared<AssumeTypeAttribute>();
	attributes_["AssumeConstness"]				= std::make_shared<AssumeConstnessAttribute>();
	attributes_["Call"]							= std::make_shared< AttributeSpawner<CallAttribute> >();

	types_["integral_type"]						= std::make_shared<CompositePrimitiveType>(CompositePrimitiveType::ListType{
		primitives_[Typename::TYPE_NAME_NAN],
		primitives_[Typename::TYPE_NAME_CHAR],
		primitives_[Typename::TYPE_NAME_UCHAR],
		primitives_[Typename::TYPE_NAME_SHORT],
		primitives_[Typename::TYPE_NAME_USHORT],
		primitives_[Typename::TYPE_NAME_INT],
		primitives_[Typename::TYPE_NAME_UINT],
		primitives_[Typename::TYPE_NAME_LONG],
		primitives_[Typename::TYPE_NAME_ULONG],
		primitives_[Typename::TYPE_NAME_LLONG],
		primitives_[Typename::TYPE_NAME_ULLONG]
	}, "integral_type");

	types_["floating_point_type"]				= std::make_shared<CompositePrimitiveType>(CompositePrimitiveType::ListType{
		primitives_[Typename::TYPE_NAME_NAN],
		primitives_[Typename::TYPE_NAME_FLOAT],
		primitives_[Typename::TYPE_NAME_DOUBLE],
		primitives_[Typename::TYPE_NAME_LDOUBLE]
	}, "floating_point_type");

	types_["numeric_type"]						= std::make_shared<CompositePrimitiveType>(CompositePrimitiveType::ListType{
		primitives_[Typename::TYPE_NAME_NAN],
		primitives_[Typename::TYPE_NAME_CHAR],
		primitives_[Typename::TYPE_NAME_UCHAR],
		primitives_[Typename::TYPE_NAME_SHORT],
		primitives_[Typename::TYPE_NAME_USHORT],
		primitives_[Typename::TYPE_NAME_INT],
		primitives_[Typename::TYPE_NAME_UINT],
		primitives_[Typename::TYPE_NAME_LONG],
		primitives_[Typename::TYPE_NAME_ULONG],
		primitives_[Typename::TYPE_NAME_LLONG],
		primitives_[Typename::TYPE_NAME_ULLONG],
		primitives_[Typename::TYPE_NAME_FLOAT],
		primitives_[Typename::TYPE_NAME_DOUBLE],
		primitives_[Typename::TYPE_NAME_LDOUBLE]
	}, "numeric_type");

	types_["primitive_type"]					= std::make_shared<CompositePrimitiveType>(CompositePrimitiveType::ListType{
		primitives_[Typename::TYPE_NAME_VOID],
		primitives_[Typename::TYPE_NAME_BOOLEAN],
		primitives_[Typename::TYPE_NAME_BIT],
		primitives_[Typename::TYPE_NAME_BYTE],
		primitives_[Typename::TYPE_NAME_NAN],
		primitives_[Typename::TYPE_NAME_CHAR],
		primitives_[Typename::TYPE_NAME_UCHAR],
		primitives_[Typename::TYPE_NAME_SHORT],
		primitives_[Typename::TYPE_NAME_USHORT],
		primitives_[Typename::TYPE_NAME_INT],
		primitives_[Typename::TYPE_NAME_UINT],
		primitives_[Typename::TYPE_NAME_LONG],
		primitives_[Typename::TYPE_NAME_ULONG],
		primitives_[Typename::TYPE_NAME_LLONG],
		primitives_[Typename::TYPE_NAME_ULLONG],
		primitives_[Typename::TYPE_NAME_FLOAT],
		primitives_[Typename::TYPE_NAME_DOUBLE],
		primitives_[Typename::TYPE_NAME_LDOUBLE],
		primitives_[Typename::TYPE_NAME_STRING],
		primitives_[Typename::TYPE_NAME_TYPE]
	}, "primitive_type");

	//Create a constant bit type & a locked attribute
	auto type = std::make_shared<DeclaredType>(bit, MemoryState(MemoryState::STATE_CONSTANT));
	auto attributes = std::make_shared<MemoryAttributes>(MemoryAttributes::ListType{ std::make_pair("Locked", attributes_["Locked"]) });

	*bit->addMemory("zero") = std::make_shared<Memory>(this, type, PrimitiveFactory::createBit(false), attributes);
	*bit->addMemory("one") = std::make_shared<Memory>(this, type, PrimitiveFactory::createBit(true), attributes);

	createString_();
}

StructuredScript::IType::Ptr StructuredScript::Storage::GlobalStorage::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name.empty())
		return nullptr;

	if (::isdigit(name[0]))
		return getPrimitiveType(static_cast<Typename>(std::stoi(name)));

	return Storage::findType(name, searchScope);
}

StructuredScript::IType::Ptr StructuredScript::Storage::GlobalStorage::getPrimitiveType(Typename type){
	auto value = primitives_.find(type);
	return (value == primitives_.end()) ? nullptr : value->second;
}

bool StructuredScript::Storage::GlobalStorage::createString_(){
	auto string = std::make_shared<Type>(this, "string");

	Parser::Parser::init();
	Parser::Parser::operatorInfo.init();

	Parser::Parser parser;
	Scanner::Scanner scanner;

	scanner.init();
	scanner.operatorSymbols.init();
	primitives_[Typename::TYPE_NAME_STRING] = string;

	std::list<std::string> lines({
		"@[Call(at)]char at(integral_type index)",
		"@[Call(append)]void append(const ref val string value)",
		"@[Call(insert)]void append(integral_type index, const ref val string value)",
		"@[Call(erase)]void erase(integral_type index, integral_type count = npos)",
		"@[Call(clear)]void clear()",
		"@[Call(substr)]string substr(integral_type index, integral_type count = npos)",
		"@[Call(find)]int find(const ref val string value, integral_type offset = 0)",
		"@[Call(find_last)]int find_last(const ref val string value, integral_type offset = 0)",
		"static const unsigned int npos = -1u"
	});

	for (auto &line : lines){
		Scanner::StringCharacterWell well(line);
		parser.parse(well, scanner, nullptr)->evaluate(string.get(), nullptr, nullptr);
	}

	string->addExternalCall("at", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	string->addExternalCall("append", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	string->addExternalCall("insert", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	string->addExternalCall("erase", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	string->addExternalCall("clear", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	string->addExternalCall("substr", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	string->addExternalCall("find", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	string->addExternalCall("find_last", [](const ArgListType &args, IStorage *storage, IExceptionManager *exception, INode *expr) -> IAny::Ptr{
		return nullptr;
	});

	return true;
}

StructuredScript::IType::Ptr StructuredScript::Storage::GlobalStorage::getPrimitiveType(int rank){
	switch (rank){
	case Objects::Primitive::CHAR_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_CHAR);
	case Objects::Primitive::UCHAR_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_UCHAR);
	case Objects::Primitive::SHORT_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_SHORT);
	case Objects::Primitive::USHORT_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_USHORT);
	case Objects::Primitive::INT_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_INT);
	case Objects::Primitive::UINT_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_UINT);
	case Objects::Primitive::LONG_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_LONG);
	case Objects::Primitive::ULONG_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_ULONG);
	case Objects::Primitive::LLONG_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_LLONG);
	case Objects::Primitive::ULLONG_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_ULLONG);
	case Objects::Primitive::FLOAT_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_FLOAT);
	case Objects::Primitive::DOUBLE_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_DOUBLE);
	case Objects::Primitive::LDOUBLE_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_LDOUBLE);
	case Objects::Primitive::STRING_RANK:
		return getPrimitiveType(Typename::TYPE_NAME_STRING);
	default:
		break;
	}

	return nullptr;
}
