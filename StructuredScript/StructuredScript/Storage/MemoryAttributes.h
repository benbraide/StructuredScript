#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_MEMORY_ATTRIBUTES_H
#define STRUCTURED_SCRIPT_STORAGE_MEMORY_ATTRIBUTES_H

namespace StructuredScript{
	namespace Storage{
		class MemoryAttribute{
		public:
			explicit MemoryAttribute(unsigned short attributes = ATTRIBUTE_NONE)
				: attributes_(attributes){}

			MemoryAttribute &operator =(unsigned short attributes);

			MemoryAttribute &operator +=(unsigned short attributes);

			MemoryAttribute &operator -=(unsigned short attributes);

			unsigned short getAttributes() const;

			bool is(unsigned short attributes, bool all = true) const;

			bool isLocked() const;

			bool isConcurrent() const;

			static const unsigned short ATTRIBUTE_NONE			= 0x0000;
			static const unsigned short ATTRIBUTE_LOCKED		= 0x0001;
			static const unsigned short ATTRIBUTE_CONCURRENT	= 0x0002;

		private:
			unsigned short attributes_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_MEMORY_ATTRIBUTES_H */