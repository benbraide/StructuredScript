#pragma once

#ifndef STRUCTURED_SCRIPT_SKIP_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_SKIP_SCANNER_PLUGIN_H

#include "Blank.h"
#include "SingleLineComment.h"
#include "MultiLineComment.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class Skip : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) override;

				virtual bool matches(ICharacterWell &well) override;

				virtual TokenType type() const override;

			private:
				Blank blank_;
				SingleLineComment singleLineComment_;
				MultiLineComment multiLineComment_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_SKIP_SCANNER_PLUGIN_H */