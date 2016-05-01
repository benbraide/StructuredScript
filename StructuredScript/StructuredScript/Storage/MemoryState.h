#pragma once

#ifndef STRUCTURED_SCRIPT_STORAGE_MEMORY_STATE_H
#define STRUCTURED_SCRIPT_STORAGE_MEMORY_STATE_H

namespace StructuredScript{
	namespace Storage{
		class MemoryState{
		public:
			explicit MemoryState(unsigned short states = STATE_NONE)
				: states_(states){}

			MemoryState &operator =(unsigned short states);

			MemoryState &operator +=(unsigned short states);

			MemoryState &operator -=(unsigned short states);

			unsigned short getStates() const;

			bool is(unsigned short states, bool all = true) const;

			bool isConstant() const;

			bool isFinal() const;

			bool isStatic() const;

			bool isPrivate() const;

			bool isProtected() const;

			bool isPublic() const;

			bool isReference() const;

			bool isRValReference() const;

			bool hasDefault() const;

			static const unsigned short STATE_NONE			= 0x0000;
			static const unsigned short STATE_CONSTANT		= 0x0001;
			static const unsigned short STATE_FINAL			= 0x0002;
			static const unsigned short STATE_STATIC		= 0x0004;
			static const unsigned short STATE_PRIVATE		= 0x0008;
			static const unsigned short STATE_PROTECTED		= 0x0010;
			static const unsigned short STATE_REFERENCE		= 0x0020;
			static const unsigned short STATE_RVALUE		= 0x0040;

		private:
			unsigned short states_;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_STORAGE_MEMORY_STATE_H */