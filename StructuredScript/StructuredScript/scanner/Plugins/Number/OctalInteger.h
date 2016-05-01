#pragma once

#ifndef STRUCTURED_SCRIPT_OCTAL_INTEGER_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_OCTAL_INTEGER_SCANNER_PLUGIN_H

#include "../../../Interfaces/IScannerPlugin.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class OctalInteger : public IScannerPlugin{
			public:
				explicit OctalInteger(const IScannerPlugin &realNumberPlugin)
					: realNumberPlugin_(&realNumberPlugin){}

				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) const override;

				virtual bool matches(const ICharacterWell &well) const override;

				virtual TokenType type() const override;

			private:
				const IScannerPlugin *realNumberPlugin_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_OCTAL_INTEGER_SCANNER_PLUGIN_H */