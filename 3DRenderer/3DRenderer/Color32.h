#pragma once
#include <iostream>
#include <memory.h>
#include "MathLib.h"

struct Color32
{
public:
	union
	{
		struct
		{
			BYTE B, G, R, A;
		};

		UINT32 ColorValue;
	};

public:
	FORCEINLINE constexpr Color32() : R(0), G(0), B(0), A(255) {};
	FORCEINLINE constexpr Color32(const BYTE& _R, const BYTE& _G, const BYTE& _B, const BYTE& _A)
	: R(_R), G(_G), B(_B), A(_A) {};

	template<typename T> requires std::is_same<Color32, T>::value
	FORCEINLINE	Color32(T&& _ref)
	: R(std::forward<BYTE>(_ref.R)), G(std::forward<BYTE>(_ref.G)),
		B(std::forward<BYTE>(_ref.B)), A(std::forward<BYTE>(_ref.A)) {};
	//완벽전달 복사생성자
	~Color32() = default;

	FORCEINLINE constexpr const UINT32& GetColorRef() const { return ColorValue; };
	FORCEINLINE constexpr UINT32& GetColorRef() { return ColorValue; };
	FORCEINLINE Color32 Get() { return std::move(Color32(1, 1, 1, 1)); }

	template<typename T> requires std::is_same<Color32, T>::value
	FORCEINLINE T& operator=(T&& _ref) noexcept
	{
		if (this == &_ref)
			return *this;

		ColorValue = std::forward<UINT>(_ref.ColorValue);

		return *this;
	};

	FORCEINLINE constexpr bool operator==(const Color32& InC) const;
	FORCEINLINE constexpr bool operator!=(const Color32& InC) const;
	FORCEINLINE constexpr void operator+=(const Color32& InC);
};

FORCEINLINE constexpr bool Color32::operator==(const Color32& InC) const
{
	return GetColorRef() == InC.GetColorRef();
};

FORCEINLINE constexpr bool Color32::operator!=(const Color32& InC) const
{
	return GetColorRef() != InC.GetColorRef();
};

FORCEINLINE constexpr void Color32::operator+=(const Color32& InC)
{
	R = (BYTE)MathLib::Clamp((BYTE)R + (BYTE)InC.R, 0, 255);
	G = (BYTE)MathLib::Clamp((BYTE)G + (BYTE)InC.G, 0, 255);
	B = (BYTE)MathLib::Clamp((BYTE)B + (BYTE)InC.B, 0, 255);
	A = (BYTE)MathLib::Clamp((BYTE)A + (BYTE)InC.A, 0, 255);
};

////////////////Color32 global operator/////////////////
FORCEINLINE Color32 operator* (const Color32& _ref, const float& _ratio)
{
	return std::move(Color32(_ref.R * _ratio, _ref.G * _ratio, _ref.B * _ratio, _ref.A * _ratio));
};

FORCEINLINE Color32 operator* (const float& _ratio, const Color32& _ref)
{
	return std::move(Color32(_ref.R * _ratio, _ref.G * _ratio, _ref.B * _ratio, _ref.A * _ratio));
};

