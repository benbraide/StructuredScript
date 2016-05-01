#pragma once

#ifndef STRUCTURED_SCRIPT_GENERIC_STRING_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_GENERIC_STRING_SCANNER_PLUGIN_H

#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			template <TokenType Type, char Quote, bool CanEscape>
			class GenericString : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override{
					if (!matches(well) && (filter == nullptr || filter(well.peek()) != IScannerPlugin::INCLUDE))
						return Token(TokenType::TOKEN_TYPE_NONE, "");

					std::string prefix = CanEscape ? std::string(1, Quote) : ("@" + std::string(1, Quote));

					well.step(static_cast<int>(prefix.size()));//Skip quote [and '@']
					well.fork();

					auto next = next_(well);
					if (next == '\0')//Missing closing quote
						return Token(TokenType::TOKEN_TYPE_ERROR, prefix + well.get());

					auto hasErrors = false, escaped = false;
					auto filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);

					while (escaped || next != Quote || filterState != IScannerPlugin::NONE){
						if (!hasErrors && filterState == IScannerPlugin::FAIL)
							hasErrors = true;

						if (!hasErrors && CanEscape){
							if (!escaped && next == '\\')
								escaped = true;
							else if (escaped)
								escaped = false;
						}

						next = next_(well);
						if (next == '\0')//Missing closing quote
							return Token(TokenType::TOKEN_TYPE_ERROR, prefix + well.get());

						filterState = (filter == nullptr) ? IScannerPlugin::NONE : filter(next);
					}

					if (hasErrors){
						well.merge();
						return Token(TokenType::TOKEN_TYPE_ERROR, well.get());
					}

					well.step(-1);
					auto value = well.get();

					well.step(1);
					well.merge();

					return Token(Type, value, prefix, std::string(1, Quote));
				}

				virtual bool matches(const ICharacterWell &well) const override{
					if (CanEscape)
						return (well.peek() == Quote);

					return (well.peek(2) == ("@" + std::string(1, Quote)));
				}

				virtual TokenType type() const override{
					return TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING;
				}

			private:
				char next_(ICharacterWell &well) const{
					auto next = well.next();
					while (next == '\0'){//Try loading more characters
						if (!well.load())
							break;

						next = well.next();
					}

					return next;
				}
			};

			typedef GenericString<TokenType::TOKEN_TYPE_DOUBLY_QUOTED_STRING, '\"', true>		DoublyQuotedString;
			typedef GenericString<TokenType::TOKEN_TYPE_DOUBLY_QUOTED_RAW_STRING, '\"', false>	DoublyQuotedRawString;

			typedef GenericString<TokenType::TOKEN_TYPE_SINGLY_QUOTED_STRING, '\'', true>		SinglyQuotedString;
			typedef GenericString<TokenType::TOKEN_TYPE_SINGLY_QUOTED_RAW_STRING, '\'', false>	SinglyQuotedRawString;

			typedef GenericString<TokenType::TOKEN_TYPE_BACK_QUOTED_STRING, '`', true>			BackQuotedString;
			typedef GenericString<TokenType::TOKEN_TYPE_BACK_QUOTED_RAW_STRING, '`', false>		BackQuotedRawString;
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_GENERIC_STRING_SCANNER_PLUGIN_H */