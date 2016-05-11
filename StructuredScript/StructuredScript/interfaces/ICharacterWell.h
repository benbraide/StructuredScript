#pragma once

#ifndef STRUCTURED_SCRIPT_CHARACTER_WELL_INTERFACE_H
#define STRUCTURED_SCRIPT_CHARACTER_WELL_INTERFACE_H

#include <string>

namespace StructuredScript{
	namespace Interfaces{
		class CharacterWell{
		public:
			virtual ~CharacterWell(){}

			virtual char peek() const = 0;

			virtual std::string peek(unsigned int length) const = 0;

			virtual std::string get() const = 0;

			virtual char next() = 0;

			virtual char prev() = 0;

			virtual void step(int steps) = 0;

			virtual void stepToEnd() = 0;

			virtual bool stepTo(char target) = 0;

			virtual void collapse() = 0;

			virtual void commit() = 0;

			virtual void fork() = 0;

			virtual void revert() = 0;

			virtual void discard() = 0;

			virtual void merge() = 0;

			virtual std::string dump() = 0;

			virtual bool load() = 0;

			virtual bool empty() const = 0;

			virtual unsigned int getLineNumber() const = 0;

			virtual unsigned int getStartIndex() const = 0;

			virtual unsigned int getEndIndex() const = 0;

			virtual std::string getOffset() const = 0;
		};
	}

	typedef Interfaces::CharacterWell ICharacterWell;
}

#endif /* !STRUCTURED_SCRIPT_CHARACTER_WELL_INTERFACE_H */