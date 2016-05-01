#pragma once

#ifndef STRUCTURED_SCRIPT_STRING_CHARACTER_WELL_H
#define STRUCTURED_SCRIPT_STRING_CHARACTER_WELL_H

#include <list>

#include "../../Interfaces/ICharacterWell.h"

namespace StructuredScript{
	namespace Scanner{
		class StringCharacterWell : public ICharacterWell{
		public:
			typedef std::list<unsigned int> ForkListType;

			explicit StringCharacterWell(const std::string &value)
				: value_(value){}

			virtual char peek() const override;

			virtual std::string peek(unsigned int length) const override;

			virtual std::string get() const override;

			virtual char next() override;

			virtual char prev() override;

			virtual void step(int steps) override;

			virtual void stepToEnd() override;

			virtual void collapse() override;

			virtual void commit() override;

			virtual void fork() override;

			virtual void revert() override;

			virtual void discard() override;

			virtual void merge() override;

			virtual std::string dump() override;

			virtual bool load() override;

			virtual bool empty() const override;

			virtual unsigned int getLineNumber() const override;

			virtual unsigned int getStartIndex() const override;

			virtual unsigned int getEndIndex() const override;

			virtual std::string getOffset() const override;

		protected:
			ForkListType forks_;
			std::string value_;
			unsigned int start_ = 0, end_ = 0, line_ = 1;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STRING_CHARACTER_WELL_H */