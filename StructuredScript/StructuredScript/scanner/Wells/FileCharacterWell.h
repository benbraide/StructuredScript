#pragma once

#ifndef STRUCTURED_SCRIPT_FILE_CHARACTER_WELL_H
#define STRUCTURED_SCRIPT_FILE_CHARACTER_WELL_H

#include <fstream>

#include "StringCharacterWell.h"

namespace StructuredScript{
	namespace Scanner{
		class FileCharacterWell : public StringCharacterWell{
		public:
			explicit FileCharacterWell(const std::string &path);

			virtual char peek() override;

			virtual std::string peek(unsigned int length) override;

			virtual char next() override;

			virtual void step(int steps) override;

			virtual bool stepTo(char target) override;

			virtual bool load() override;

			bool fail() const;

		protected:
			bool stepTo_(char target, unsigned int offset);

			std::ifstream file_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_FILE_CHARACTER_WELL_H */