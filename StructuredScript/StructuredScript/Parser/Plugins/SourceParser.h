#pragma once

#ifndef STRUCTURED_SCRIPT_SOURCE_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_SOURCE_PARSER_PLUGIN_H

#include "../../Common/ExceptionManagerQuery.h"
#include "../../Common/NodeQuery.h"
#include "../../Common/Factory.h"

#include "../../Interfaces/IParserPlugin.h"

namespace StructuredScript{
	namespace Parser{
		template <class NodeType, bool AcceptEmptyValue>
		class SourceParser : public IParserPlugin{
		public:
			SourceParser(const std::string &name)
				: name_(name){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

		private:
			std::string name_;
		};

		template <class NodeType, bool AcceptEmptyValue>
		INode::Ptr StructuredScript::Parser::SourceParser<NodeType, AcceptEmptyValue>::parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception){
			scanner.fork(';');//Seperate multiple declarations
			auto value = parser.expression(nullptr, well, scanner, exception);

			scanner.close(well, true);
			if (Query::ExceptionManager::has(exception))
				return nullptr;

			if (!AcceptEmptyValue && Query::Node::isEmpty(value))
				return Query::ExceptionManager::setAndReturnNode(exception, PrimitiveFactory::createString("'" + name_ + "': Expression expected after!"));

			return std::make_shared<NodeType>(value);
		}

	}
}

#endif /* !STRUCTURED_SCRIPT_SOURCE_PARSER_PLUGIN_H */