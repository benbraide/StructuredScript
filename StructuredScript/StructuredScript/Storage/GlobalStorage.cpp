#include "GlobalStorage.h"

void StructuredScript::Storage::GlobalStorage::init(){
	Parser::Parser::init();
	Scanner::Scanner::init();

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
	primitives_[Typename::TYPE_NAME_TYPE]		= std::make_shared<PrimitiveType>("type", Typename::TYPE_NAME_TYPE);

	attributes_["Locked"]						= std::make_shared<LockedAttribute>();
	attributes_["Concurrent"]					= std::make_shared<ConcurentAttribute>();
	attributes_["Once"]							= std::make_shared<OnceAttribute>();
	attributes_["Override"]						= std::make_shared<OverrideAttribute>();
	attributes_["AssumeType"]					= std::make_shared<AssumeTypeAttribute>();
	attributes_["AssumeConstness"]				= std::make_shared<AssumeConstnessAttribute>();
	attributes_["RightUnary"]					= std::make_shared<RightUnaryAttribute>();
	attributes_["UnaryRight"]					= std::make_shared<RightUnaryAttribute>();
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

	Objects::FunctionObject::init();
	Objects::String::init();

	types_["primitive_type"] = std::make_shared<CompositePrimitiveType>(CompositePrimitiveType::ListType{
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
		primitives_[Typename::TYPE_NAME_TYPE],
		findType("function_type"),
		findType("string")
	}, "primitive_type");

	//Create a constant bit type & a locked attribute
	auto type = std::make_shared<DeclaredType>(bit, MemoryState(MemoryState::STATE_CONSTANT));
	auto attributes = std::make_shared<MemoryAttributes>(MemoryAttributes::ListType{ std::make_pair("Locked", attributes_["Locked"]) });

	*bit->addMemory("zero") = std::make_shared<Memory>(this, type, PrimitiveFactory::createBit(false), attributes);
	*bit->addMemory("one") = std::make_shared<Memory>(this, type, PrimitiveFactory::createBit(true), attributes);

	Objects::Expansion::init();
	Objects::ArrayObject::init();
}

StructuredScript::IType::Ptr StructuredScript::Storage::GlobalStorage::findType(const std::string &name, unsigned short searchScope /*= SEARCH_DEFAULT*/){
	if (name.empty())
		return nullptr;

	if (::isdigit(name[0]))
		return getPrimitiveType(static_cast<Typename>(std::stoi(name)));

	for (auto &primitive : primitives_){
		if (primitive.second->name() == name)
			return primitive.second;
	}

	return Storage::findType(name, searchScope);
}

StructuredScript::IType::Ptr StructuredScript::Storage::GlobalStorage::getPrimitiveType(Typename type){
	if (type == Typename::TYPE_NAME_STRING)
		return findType("string", SEARCH_LOCAL);

	if (type == Typename::TYPE_NAME_FUNCTION)
		return findType("function_type", SEARCH_LOCAL);

	auto value = primitives_.find(type);
	return (value == primitives_.end()) ? nullptr : value->second;
}

StructuredScript::INode::Ptr StructuredScript::Storage::GlobalStorage::parse(const std::string &value){
	Parser::Parser parser;
	Scanner::Scanner scanner;

	ExceptionManager xManager;
	Scanner::StringCharacterWell well(value);

	return parser.parse(well, scanner, &xManager);
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
		return findType("string", SEARCH_LOCAL);
	default:
		break;
	}

	return nullptr;
}
