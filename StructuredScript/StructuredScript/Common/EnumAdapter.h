#pragma once

#ifndef STRUCTURED_SCRIPT_ENUM_ADAPTER_H
#define STRUCTURED_SCRIPT_ENUM_ADAPTER_H

namespace StructuredScript{
	template <class EnumType, int Value>
	class EnumAdapter{
	public:
		operator EnumType() const{
			return static_cast<EnumType>(Value);
		}

		operator int() const{
			return Value;
		}

		bool operator <(EnumType right) const{
			return (Value < static_cast<int>(right));
		}

		friend bool operator <(EnumType left, const EnumAdapter &right){
			return (static_cast<int>(right) < Value);
		}

		bool operator <=(EnumType right) const{
			return (Value <= static_cast<int>(right));
		}

		friend bool operator <=(EnumType left, const EnumAdapter &right){
			return (static_cast<int>(right) <= Value);
		}

		bool operator ==(EnumType right) const{
			return (Value == static_cast<int>(right));
		}

		friend bool operator ==(EnumType left, const EnumAdapter &right){
			return (static_cast<int>(right) == Value);
		}

		bool operator >=(EnumType right) const{
			return (Value >= static_cast<int>(right));
		}

		friend bool operator >=(EnumType left, const EnumAdapter &right){
			return (static_cast<int>(right) >= Value);
		}

		bool operator >(EnumType right) const{
			return (Value > static_cast<int>(right));
		}

		friend bool operator >(EnumType left, const EnumAdapter &right){
			return (static_cast<int>(right) > Value);
		}

		bool operator <(int right) const{
			return (Value < right);
		}

		friend bool operator <(int left, const EnumAdapter &right){
			return (right < Value);
		}

		bool operator <=(int right) const{
			return (Value <= right);
		}

		friend bool operator <=(int left, const EnumAdapter &right){
			return (right <= Value);
		}

		bool operator ==(int right) const{
			return (Value == right);
		}

		friend bool operator ==(int left, const EnumAdapter &right){
			return (right == Value);
		}

		bool operator >=(int right) const{
			return (Value >= right);
		}

		friend bool operator >=(int left, const EnumAdapter &right){
			return (right >= Value);
		}

		bool operator >(int right) const{
			return (Value > right);
		}

		friend bool operator >(int left, const EnumAdapter &right){
			return (right > Value);
		}
	};

	template <class EnumType, EnumType Base, int Value>
	class StaticEnumAdapter{
	public:
		static const EnumType type = static_cast<EnumType>(static_cast<int>(Base) + Value);

		static const int value = static_cast<int>(Base) + Value;
	};
}

#endif /* !STRUCTURED_SCRIPT_ENUM_ADAPTER_H */