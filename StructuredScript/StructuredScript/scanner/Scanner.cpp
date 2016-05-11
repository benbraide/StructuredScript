#include "Scanner.h"

void StructuredScript::Scanner::Scanner::init(){
	plugins_.clear();

	plugins_.push_back(&identifierPlugin_);
	plugins_.push_back(&stringPlugin_);

	plugins_.push_back(&numberPlugin_);
	plugins_.push_back(&symbolPlugin_);
}

StructuredScript::Scanner::Scanner::Token StructuredScript::Scanner::Scanner::next(ICharacterWell &well, const PluginListType &plugins){
	if (!hasMore(well))
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto token = getSaved_(true);
	if (token.type() != TokenType::TOKEN_TYPE_NONE)
		return token;

	if (token.type() == TokenType::TOKEN_TYPE_ERROR)
		return token;

	token = get_(well, plugins);
	if (token.type() == TokenType::TOKEN_TYPE_NONE)
		token = get_(well, plugins_);

	well.commit();
	if (token.type() != TokenType::TOKEN_TYPE_NONE)
		return token;

	switch (well.peek()){
	case '(':
		return Token(TokenType::TOKEN_TYPE_GROUP, "(");
	case '[':
		return Token(TokenType::TOKEN_TYPE_INDEX, "[");
	case '{':
		return Token(TokenType::TOKEN_TYPE_BLOCK, "{");
	default:
		break;
	}

	return Token(TokenType::TOKEN_TYPE_NONE, "");
}

StructuredScript::Scanner::Scanner::Token StructuredScript::Scanner::Scanner::peek(ICharacterWell &well, const PluginListType &plugins){
	auto token = next(well, plugins);
	save(token);

	return token;
}

void StructuredScript::Scanner::Scanner::save(const Token &token){
	if (token.type() != TokenType::TOKEN_TYPE_NONE)
		savedTokens_.push_back(token);
}

bool StructuredScript::Scanner::Scanner::fork(char closeWith){
	if (closeWith == '\0')
		return false;

	openList_.push_back(closeWith_ = closeWith);

	return true;
}

bool StructuredScript::Scanner::Scanner::open(ICharacterWell &well, char target, char closeWith){
	if (!verifyTarget_(well, target, true))
		return false;

	if (closeWith == '\0')
		openList_.push_back(closeWith_ = getCloseWith_(target));
	else
		openList_.push_back(closeWith_ = closeWith);

	return true;
}

bool StructuredScript::Scanner::Scanner::close(ICharacterWell &well, bool force/* = false*/){
	if (!force && (openList_.empty() || !verifyTarget_(well, closeWith_, false)))
		return false;

	openList_.pop_back();
	closeWith_ = openList_.empty() ? '\0' : *openList_.rbegin();

	return true;
}

bool StructuredScript::Scanner::Scanner::hasMore(ICharacterWell &well){
	return hasMore_(well, true);
}

const StructuredScript::IScannerPlugin *StructuredScript::Scanner::Scanner::getPlugin(TokenType target) const{
	for (auto plugin : plugins_){
		if (plugin->type() == target)
			return plugin;
	}

	if (skipPlugin_.type() == target)
		return &skipPlugin_;

	return nullptr;
}

StructuredScript::Scanner::Scanner::Token StructuredScript::Scanner::Scanner::get_(ICharacterWell &well, const PluginListType &plugins){
	for (auto plugin : plugins){
		auto token = plugin->get(well);
		if (token.type() == TokenType::TOKEN_TYPE_NONE)
			continue;

		if (token.type() == TokenType::TOKEN_TYPE_ERROR)
			return token;

		switch (token.type()){
		case TokenType::TOKEN_TYPE_IDENTIFIER:
			return extendIdentifier_(well, token);
		case TokenType::TOKEN_TYPE_DECIMAL_INTEGER:
			return extendDecimalInteger_(well, token);
		case TokenType::TOKEN_TYPE_SYMBOL:
			return extendSymbol_(well, token);
		default:
			break;
		}

		return token.isGroup(TokenGroup::TOKEN_GROUP_NUMBER) ? extendNumber_(well, token) : token;
	}

	return Token(TokenType::TOKEN_TYPE_NONE, "");
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Scanner::extendIdentifier_(ICharacterWell &well, const Token &token){
	auto id = typenameIdentifierPlugin_.get(well);//Try typename identifier
	if (id.type() != TokenType::TOKEN_TYPE_NONE)
		return id;

	auto value = token.value();
	if (value == "NaN")
		return Token(NaNTokenType::type, value, token.prefix(), token.suffix(), token.skipValue(), token.prefixOffset());

	if (value == "true")
		return Token(TrueTokenType::type, value, token.prefix(), token.suffix(), token.skipValue(), token.prefixOffset());

	if (value == "false")
		return Token(FalseTokenType::type, value, token.prefix(), token.suffix(), token.skipValue(), token.prefixOffset());

	return token;
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Scanner::extendDecimalInteger_(ICharacterWell &well, const Token &token){
	auto radixInteger = radixIntegerPlugin_.get(well);
	return extendNumber_(well, (radixInteger.type() == TokenType::TOKEN_TYPE_NONE) ? token : radixInteger);
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Scanner::extendNumber_(ICharacterWell &well, const Token &token){
	well.fork();
	auto suffix = identifierPlugin_.get(well);

	well.merge();
	if (suffix.type() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, token.str() + suffix.value());

	return Token(token.type(), token.value(), token.prefix(), token.suffix() + suffix.value(), token.skipValue(), token.prefixOffset());
}

StructuredScript::Scanner::Token StructuredScript::Scanner::Scanner::extendSymbol_(ICharacterWell &well, const Token &token){
	if (token.value() == "#"){//Preprocessor
		auto suffix = identifierPlugin_.get(well);
		if (suffix.type() != TokenType::TOKEN_TYPE_IDENTIFIER)
			return Token(TokenType::TOKEN_TYPE_ERROR, token.value() + suffix.value());

		return Token(TokenType::TOKEN_TYPE_PREPROCESSOR, suffix.value(), "#");
	}

	return token;
}

StructuredScript::Scanner::Scanner::Token StructuredScript::Scanner::Scanner::getSaved_(bool remove){
	if (savedTokens_.empty())
		return Token(TokenType::TOKEN_TYPE_NONE, "");

	auto token = *savedTokens_.rbegin();
	if (remove)
		savedTokens_.pop_back();

	return token;
}

void StructuredScript::Scanner::Scanner::dropSaved_(){
	if (!savedTokens_.empty())
		savedTokens_.pop_back();
}

char StructuredScript::Scanner::Scanner::getCloseWith_(char target) const{
	switch (target){
	case '(':
		return ')';
	case '[':
		return ']';
	case '{':
		return '}';
	case '<':
		return '>';
	default:
		break;
	}

	return '\0';
}

bool StructuredScript::Scanner::Scanner::verifyTarget_(ICharacterWell &well, char target, bool check){
	if (!hasMore_(well, check))
		return false;

	auto saved = getSaved_(false);
	if (target != '\0'){//Verify that next character is target
		if (saved.type() == TokenType::TOKEN_TYPE_NONE){
			if (well.peek() != target)//Target failed to match next character
				return false;
		}
		else if (saved.value() != std::string(1, target))//Target failed to match next character
			return false;
	}

	if (saved.type() == TokenType::TOKEN_TYPE_NONE){//Skip character
		well.step(1);
		well.commit();
	}
	else
		dropSaved_();

	return true;
}

bool StructuredScript::Scanner::Scanner::hasMore_(ICharacterWell &well, bool check){
	if (!savedTokens_.empty())
		return (closeWith_ == '\0' || getSaved_(false).value() != std::string(1, closeWith_));

	well.fork();
	auto token = skip_(well);//Skip blanks and comments
	if (token.type() == TokenType::TOKEN_TYPE_ERROR)
		well.revert();
	else
		well.discard();

	auto next = well.peek();
	return (next != '\0' && (!check || next != closeWith_));
}

StructuredScript::Scanner::Scanner::Token StructuredScript::Scanner::Scanner::skip_(ICharacterWell &well) const{
	auto blank = skipPlugin_.get(well);
	if (blank.type() == TokenType::TOKEN_TYPE_ERROR)
		return Token(TokenType::TOKEN_TYPE_ERROR, well.get());

	while (blank.type() != TokenType::TOKEN_TYPE_NONE){
		blank = skipPlugin_.get(well);
		if (blank.type() == TokenType::TOKEN_TYPE_ERROR)
			return Token(TokenType::TOKEN_TYPE_ERROR, well.get());
	}

	return Token(TokenType::TOKEN_TYPE_NONE, "");
}

bool StructuredScript::Scanner::tokenIsLiteralType(TokenType type){
	if (tokenIsNumberType(type) || tokenIsStringType(type))
		return true;

	return  (type == NaNTokenType::type || type == TrueTokenType::type || type == FalseTokenType::type);
}

StructuredScript::Symbols StructuredScript::Scanner::Scanner::operatorSymbols;

StructuredScript::Scanner::Plugins::Identifier StructuredScript::Scanner::Scanner::identifierPlugin_;
StructuredScript::Scanner::Plugins::TypenameIdentifier StructuredScript::Scanner::Scanner::typenameIdentifierPlugin_;

StructuredScript::Scanner::Plugins::Number StructuredScript::Scanner::Scanner::numberPlugin_;
StructuredScript::Scanner::Plugins::RadixInteger StructuredScript::Scanner::Scanner::radixIntegerPlugin_;

StructuredScript::Scanner::Plugins::Symbol StructuredScript::Scanner::Scanner::symbolPlugin_(Scanner::operatorSymbols);

StructuredScript::Scanner::Plugins::String StructuredScript::Scanner::Scanner::stringPlugin_;
StructuredScript::Scanner::Plugins::Skip StructuredScript::Scanner::Scanner::skipPlugin_;
