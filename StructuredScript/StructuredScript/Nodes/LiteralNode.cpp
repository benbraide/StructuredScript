#include "LiteralNode.h"

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::LiteralNode::ptr(){
	return shared_from_this();
}

StructuredScript::Interfaces::Node::Ptr StructuredScript::Nodes::LiteralNode::clone(){
	return std::make_shared<LiteralNode>(value_);
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::LiteralNode::evaluate(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto type = value_.type();
	if (tokenIsNumberType(type))
		return evaluateNumber_(storage, exception, expr);

	if (tokenIsStringType(type)){
		auto value = tokenIsRawStringType(type) ? escapeString_() : value_.value();
		auto suffix = Scanner::Suffix::get(value_.suffix().substr(1));
		if (suffix == Scanner::SuffixType::SUFFIX_TYPE_ERROR)
			return nullptr;//TODO: Throw exception

		if (type == Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING || type == Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_RAW_STRING){
			if (suffix == Scanner::SuffixType::SUFFIX_TYPE_UNSIGNED)
				return PrimitiveFactory::createUChar('\0');

			if (suffix != Scanner::SuffixType::SUFFIX_TYPE_NONE)
				return nullptr;//TODO: Throw exception

			return PrimitiveFactory::createChar('\0');
		}

		if (suffix != Scanner::SuffixType::SUFFIX_TYPE_NONE)
			return nullptr;//TODO: Throw exception

		if (type == Scanner::TokenType::TOKEN_TYPE_BACK_QUOTED_STRING || type == Scanner::TokenType::TOKEN_TYPE_BACK_QUOTED_RAW_STRING)
			return nullptr;

		return PrimitiveFactory::createString(value);
	}

	switch (type){
	case Scanner::NaNTokenType::type:
		return PrimitiveFactory::createNaN();
	case Scanner::TrueTokenType::type:
		return PrimitiveFactory::createBool(true);
	case Scanner::FalseTokenType::type:
		return PrimitiveFactory::createBool(false);
	default:
		break;
	}

	return nullptr;
}

std::string StructuredScript::Nodes::LiteralNode::str(){
	return value_.str();
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::LiteralNode::evaluateNumber_(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto suffix = Scanner::Suffix::get(value_.suffix());
	if (suffix == Scanner::SuffixType::SUFFIX_TYPE_ERROR)
		return nullptr;//TODO: Throw exception

	if ((Scanner::tokenIsIntegerType(value_.type()) && !Scanner::Suffix::isCompatibleWithInteger(suffix)) ||
		(Scanner::tokenIsRealType(value_.type()) && !Scanner::Suffix::isCompatibleWithRealNumber(suffix))){
		return nullptr;//TODO: Throw exception
	}

	switch (suffix){
	case Scanner::SuffixType::SUFFIX_TYPE_SHORT:
		return PrimitiveFactory::createShort(getValue_<short>());
	case Scanner::SuffixType::SUFFIX_TYPE_USHORT:
		return PrimitiveFactory::createUShort(getValue_<unsigned short>());
	case Scanner::SuffixType::SUFFIX_TYPE_UNSIGNED:
		return PrimitiveFactory::createUInt(getValue_<unsigned int>());
	case Scanner::SuffixType::SUFFIX_TYPE_LONG:
		if (Scanner::tokenIsRealType(value_.type()))
			return PrimitiveFactory::createLDouble(getValue_<long double>());
		return PrimitiveFactory::createLong(getValue_<long>());
	case Scanner::SuffixType::SUFFIX_TYPE_ULONG:
		return PrimitiveFactory::createULong(getValue_<unsigned long>());
	case Scanner::SuffixType::SUFFIX_TYPE_LLONG:
		return PrimitiveFactory::createLLong(getValue_<long long>());
	case Scanner::SuffixType::SUFFIX_TYPE_ULLONG:
		return PrimitiveFactory::createULLong(getValue_<unsigned long long>());
	case Scanner::SuffixType::SUFFIX_TYPE_FLOAT:
		return PrimitiveFactory::createFloat(getValue_<float>());
	default:
		break;
	}

	if (Scanner::tokenIsRealType(value_.type()))
		return PrimitiveFactory::createDouble(getValue_<double>());

	if (value_.type() == Scanner::TokenType::TOKEN_TYPE_BINARY_INTEGER && value_.value().size() == 8u)
		return PrimitiveFactory::createByte(getValue_<unsigned char>());

	return PrimitiveFactory::createInt(getValue_<int>());
}

long double StructuredScript::Nodes::LiteralNode::parseExponent_() const{
	auto value = value_.value();

	auto index = value.find('e');
	if (index >= value.size())
		index = value.find('E');

	return (std::stold(value.substr(0, index)) * std::pow(10, std::stold(value.substr(index + 1))));
}

std::string StructuredScript::Nodes::LiteralNode::escapeString_() const{
	return "";
}
