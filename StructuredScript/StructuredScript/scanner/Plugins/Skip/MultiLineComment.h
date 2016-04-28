#pragma once

#ifndef STRUCTURED_SCRIPT_MULTI_LINE_COMMENT_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_MULTI_LINE_COMMENT_SCANNER_PLUGIN_H

#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class MultiLineComment : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				char next_(ICharacterWell &well) const;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_MULTI_LINE_COMMENT_SCANNER_PLUGIN_H */