#pragma once
#include "Color32.h"

class RenderData
{
public:
	float X, Y;
	Color32 Color;

public:
	RenderData() = default;
	RenderData(const float& _X, const float& _Y, const Color32 _Col)
	: X(_X), Y(_Y), Color(_Col)	{};

public:
	template<typename T> requires std::is_same_v<T, RenderData>
	FORCEINLINE RenderData operator= (T&& _Ref) noexcept
	{
		if (&_Ref == this)
			return *this;

		X = std::forward<float>(_Ref.X);
		Y = std::forward<float>(_Ref.Y);
		Color = std::forward<float>(_Ref.Color);

		return *this;
	}

};

