#pragma once

#ifndef STRUCTURED_SCRIPT_STRING_SCANNER_PLUGIN_H
#define STRUCTURED_SCRIPT_STRING_SCANNER_PLUGIN_H

#include "GenericString.h"

namespace StructuredScript{
	namespace Scanner{
		namespace Plugins{
			class String : public IScannerPlugin{
			public:
				virtual Token get(ICharacterWell &well, FilterType filter = nullptr) override;

				virtual bool matches(ICharacterWell &well) override;

				virtual TokenType type() const override;

			private:
				DoublyQuotedString doublyQuotedString_;
				DoublyQuotedRawString doublyQuotedRawString_;

				SinglyQuotedString singlyQuotedString_;
				SinglyQuotedRawString singlyQuotedRawString_;

				BackQuotedString backQuotedString_;
				BackQuotedRawString backQuotedRawString_;
			};
		}
	}
}

#endif /* !STRUCTURED_SCRIPT_STRING_SCANNER_PLUGIN_H */