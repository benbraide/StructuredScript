#pragma once

#ifndef STRUCTURED_SCRIPT_MEMORY_STATE_PARSER_PLUGIN_H
#define STRUCTURED_SCRIPT_MEMORY_STATE_PARSER_PLUGIN_H

#include "../../Interfaces/IParserPlugin.h"
#include "../../Nodes/DeclarationNode.h"

namespace StructuredScript{
	namespace Parser{
		class MemoryStateParser : public IParserPlugin{
		public:
			MemoryStateParser(const std::string &value)
				: state_(translate(value)){}

			virtual INode::Ptr parse(ICharacterWell &well, IScanner &scanner, IParser &parser, IExceptionManager *exception) override;

			const Storage::MemoryState &state() const;

			static unsigned short translate(const std::string &state);

		private:
			Storage::MemoryState state_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_MEMORY_STATE_PARSER_PLUGIN_H */