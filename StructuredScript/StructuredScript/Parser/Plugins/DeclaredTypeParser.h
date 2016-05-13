#pragma once

#ifndef STRUCTURED_SCRIPT_DECLARED_TYPE_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_DECLARED_TYPE_PARSER_PLUGIN_H

#include "../../Common/ExceptionManagerQuery.h"
#include "../../Common/NodeQuery.h"
#include "../../Common/Factory.h"
#include "../../Common/Types/DeclaredType.h"

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/IdentifierNode.h"
#include "../../Scanner/Plugins/Identifier/TypenameIdentifier.h"

namespace StructuredScript{
	namespace Parser{
		class DeclaredTypeParser : public IParserPlugin{
		public:
			DeclaredTypeParser(const std::string &value)
				: state_(translate(value)){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

			const Storage::MemoryState &state() const;

			static unsigned short translate(const std::string &state);

		private:
			Storage::MemoryState state_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_DECLARED_TYPE_PARSER_PLUGIN_H */