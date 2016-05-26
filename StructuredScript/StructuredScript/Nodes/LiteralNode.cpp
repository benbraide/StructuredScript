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
		auto suffixValue = value_.suffix().substr(1);
		auto value = tokenIsRawStringType(type) ? value_.value() : escapeString_(exception, expr);

		auto suffix = Scanner::Suffix::get(suffixValue);
		if (suffix == Scanner::SuffixType::SUFFIX_TYPE_ERROR)
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString("'" + value_.str() + "': Bad suffix!"));

		if (type == Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING || type == Scanner::TokenType::TOKEN_TYPE_SINGLY_QUOTED_RAW_STRING){
			if (value.empty())
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(value_.str() + ": Bad character value!"));

			if (suffix == Scanner::SuffixType::SUFFIX_TYPE_UNSIGNED)
				return PrimitiveFactory::createUChar(value[0]);

			if (suffix != Scanner::SuffixType::SUFFIX_TYPE_NONE)
				return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(value_.str() + ": Bad suffix!"));

			return PrimitiveFactory::createChar(value[0]);
		}

		if (suffix != Scanner::SuffixType::SUFFIX_TYPE_NONE)
			return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString(value_.str() + ": Bad suffix!"));

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

	return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString("'" + value_.str() + "': Unrecognized literal!"));
}

std::string StructuredScript::Nodes::LiteralNode::str(){
	return value_.str();
}

void StructuredScript::Nodes::LiteralNode::attributes(IMemoryAttributes::Ptr attributes){}

StructuredScript::Scanner::Token StructuredScript::Nodes::LiteralNode::value(){
	return value_;
}

void StructuredScript::Nodes::LiteralNode::value(const Scanner::Token &value){
	value_ = value;
}

StructuredScript::IMemoryAttributes::Ptr StructuredScript::Nodes::LiteralNode::attributes(){
	return nullptr;
}

StructuredScript::IAny::Ptr StructuredScript::Nodes::LiteralNode::evaluateNumber_(IStorage *storage, IExceptionManager *exception, INode *expr){
	auto suffix = Scanner::Suffix::get(value_.suffix());
	if (suffix == Scanner::SuffixType::SUFFIX_TYPE_ERROR)
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString("'" + value_.str() + "': Bad suffix!"));

	if ((Scanner::tokenIsIntegerType(value_.type()) && !Scanner::Suffix::isCompatibleWithInteger(suffix)) ||
		(Scanner::tokenIsRealType(value_.type()) && !Scanner::Suffix::isCompatibleWithRealNumber(suffix))){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString("'" + value_.str() + "': Bad suffix!"));
	}

	try{
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
	catch (...){
		return Query::ExceptionManager::setAndReturnObject(exception, PrimitiveFactory::createString("'" + value_.str() + "': Bad numerical value!"));
	}
}

long double StructuredScript::Nodes::LiteralNode::parseExponent_() const{
	auto value = value_.value();

	auto index = value.find('e');
	if (index >= value.size())
		index = value.find('E');

	return (std::stold(value.substr(0, index)) * std::pow(10, std::stold(value.substr(index + 1))));
}

std::string StructuredScript::Nodes::LiteralNode::escapeString_(IExceptionManager *exception, INode *expr) const{
	Scanner::Plugins::HexadecimalInteger hexadecimalIntegerPlugin;
	Scanner::Plugins::OctalInteger octalIntegerPlugin;
	Scanner::Plugins::DecimalInteger decimalIntegerPlugin;

	std::string value;
	Scanner::StringCharacterWell well(value_.value());

	well.fork();
	while (well.stepTo('\\')){
		value += well.get();//Add characters before '\'
		well.merge();

		well.step(1);
		well.fork();
		
		bool firstEntry = true;
		auto token = hexadecimalIntegerPlugin.get(well, [&firstEntry](char next) -> unsigned short{
			if (firstEntry){
				firstEntry = false;
				return (next == 'x') ? IScannerPlugin::INCLUDE : IScannerPlugin::NONE;
			}

			return IScannerPlugin::NONE;
		});

		if (token.type() == Scanner::TokenType::TOKEN_TYPE_NONE){
			token = octalIntegerPlugin.get(well);
			if (token.type() == Scanner::TokenType::TOKEN_TYPE_NONE)
				token = decimalIntegerPlugin.get(well);
		}

		auto type = token.type();
		if (type != Scanner::TokenType::TOKEN_TYPE_NONE && type != Scanner::TokenType::TOKEN_TYPE_ERROR){
			well.merge();
			try{
				switch (type){
				case Scanner::TokenType::TOKEN_TYPE_HEXADECIMAL_INTEGER:
					value += static_cast<char>(std::stoi(token.value(), nullptr, 16));
					break;
				case Scanner::TokenType::TOKEN_TYPE_OCTAL_INTEGER:
					value += static_cast<char>(std::stoi(token.value(), nullptr, 8));
					break;
				default:
					value += static_cast<char>(std::stoi(token.value()));
					break;
				}
			}
			catch (...){
				Query::ExceptionManager::set(exception, PrimitiveFactory::createString(value_.str() + ": Bad numerical value!"));
			}
		}
		else{
			well.discard();
			value += getEscapedCharacter_(well.next());
		}

		well.fork();
	}

	well.stepToEnd();
	value += well.get();//Add trailing characters
	well.merge();

	return value;
}

char StructuredScript::Nodes::LiteralNode::getEscapedCharacter_(char value) const{
	switch (value){
	case '0':
		return '\0';
	case 'a':
		return '\a';
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	default:
		break;
	}

	return value;
}
