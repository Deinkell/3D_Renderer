#pragma once
#include <Windows.h>
#include <concepts>

namespace MathLib
{
	template<class T> requires std::is_fundamental_v<T>
	FORCEINLINE static constexpr T Clamp(const T X, const T Min, const T Max)
	{
		return X < Min ? Min : X < Max ? X : Max;
	};
};
