#pragma once

#ifndef STRUCTURED_SCRIPT_EXPRESSION_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_EXPRESSION_PARSER_PLUGIN_H

#include "../../Common/ExceptionManagerQuery.h"
#include "../../Common/NodeQuery.h"
#include "../../Common/Factory.h"

#include "../../Interfaces/IParserPlugin.h"

namespace StructuredScript{
	namespace Parser{
		template <class NodeType, bool AcceptEmptyValue>
		class ExpressionParser : public IParserPlugin{
		public:
			ExpressionParser(const std::string &name)
				: name_(name){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			std::string name_;
		};

		template <class NodeType, bool AcceptEmptyValue>
		INode::Ptr StructuredScript::Parser::ExpressionParser<NodeType, AcceptEmptyValue>::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
			INode::Ptr value;
			if (scanner.peek(well).value() != "("){
				scanner.fork(';');//Single line

				auto firstEntry = true;
				auto value = parser.expression(nullptr, well, scanner, exception, -1, [&firstEntry](const Scanner::Token &next) -> bool{
					if (firstEntry){
						firstEntry = false;
						return true;
					}

					if (next.type() == Scanner::TokenType::TOKEN_TYPE_SYMBOL)
						return (next.type() == Scanner::TokenType::TOKEN_TYPE_IDENTIFIER);

					auto value = next.value();
					return (value == "::" || value == "." || value == "(" || value == "[" || value == "()" || value == "[]");
				});

				scanner.close(well, true);
			}
			else{//Use group as expression
				scanner.open(well, '(', ')');
				value = parser.expression(nullptr, well, scanner, exception);
				if (!scanner.close(well) && !Query::ExceptionManager::has(exception)){
					Query::ExceptionManager::set(exception, PrimitiveFactory::createString(
						name_ + "'(" + value->str() + "...': Bad expression!"));
				}
			}

			if (Query::ExceptionManager::has(exception))
				return nullptr;

			if (!AcceptEmptyValue && Query::Node::isEmpty(value))
				return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + name_ + "': Expression expected after!"));

			return std::make_shared<NodeType>(value);
		}

	}
}

#endif /* !STRUCTURED_SCRIPT_EXPRESSION_PARSER_PLUGIN_H */