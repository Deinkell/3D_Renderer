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
	Color32(T&& _ref)
	: R(std::forward<BYTE>(_ref.R)), G(std::forward<BYTE>(_ref.G)),
		B(std::forward<BYTE>(_ref.B)), A(std::forward<BYTE>(_ref.A)) {};
	//완벽전달 복사생성자
	~Color32() = default;

	FORCEINLINE constexpr const UINT32& GetColorRef() const { return ColorValue; };
	FORCEINLINE constexpr UINT32& GetColorRef() { return ColorValue; };
	FORCEINLINE Color32 Get() { return std::move(Color32(1, 1, 1, 1)); }

	template<typename T> requires std::is_same<Color32, T>::value
	FORCEINLINE constexpr T& operator=(T&& _ref) noexcept
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
}

FORCEINLINE constexpr bool Color32::operator!=(const Color32& InC) const
{
	return GetColorRef() != InC.GetColorRef();
}

FORCEINLINE constexpr void Color32::operator+=(const Color32& InC)
{
	R = (BYTE)MathLib::Clamp((BYTE)R + (BYTE)InC.R, 0, 255);
	G = (BYTE)MathLib::Clamp((BYTE)G + (BYTE)InC.G, 0, 255);
	B = (BYTE)MathLib::Clamp((BYTE)B + (BYTE)InC.B, 0, 255);
	A = (BYTE)MathLib::Clamp((BYTE)A + (BYTE)InC.A, 0, 255);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
struct Vector3
{
public:
	float X, Y, Z;

public:
	FORCEINLINE constexpr Vector3() : X(0.f), Y(0.f), Z(0.f) {};
	FORCEINLINE constexpr Vector3(float& _x, float& _y, float& _z) : X(_x), Y(_y), Z(_z) {};
	//복사생성
	FORCEINLINE constexpr Vector3(float&& _x, float&& _y, float&& _z)
	: X(std::move(_x)), Y(std::move(_y)), Z(std::move(_z)) {};
	//이동생성
	template<typename T> requires std::is_same<Vector3, T>::value
	Vector3(T&& _ref)
	: X(std::forward<float>(_ref.X)), Y(std::forward<float>(_ref.Y)), Z(std::forward<float>(_ref.Z)) {};
	//완벽전달 생성자
	float GetX() { return X; };
	float GetY() { return Y; };
	float GetZ() { return Z; };
	Vector3 GetVec3() { return std::move(Vector3(X, Y, Z)); };

	template<typename T> requires std::is_same<Vector3, T>::value
	FORCEINLINE constexpr T& operator=(T&& _ref) noexcept
	{
		if (this == &_ref)
			return *this;

		X = std::forward<float>(_ref.X);
		Y = std::forward<float>(_ref.Y);
		Z = std::forward<float>(_ref.Z);

		return *this;
	};

	FORCEINLINE constexpr void operator+= (const Vector3& _ref);

	~Vector3() = default;
};


//Vector3 연산관련 오퍼레이터
FORCEINLINE constexpr void Vector3::operator+= (const Vector3& _ref)
{
	X = X + _ref.X;
	Y = Y + _ref.Y;
	Z = Z + _ref.Z;
};
//Vector3 연산관련 오퍼레이터
////////////////Vec3 global operator/////////////////
FORCEINLINE Vector3 operator+ (const Vector3& _ref1, const Vector3& _ref2)
{
	return std::move(Vector3((_ref1.X + _ref2.X), (_ref1.Y + _ref2.Y), (_ref1.Z + _ref2.Z)));
}//Vector3 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Vector3 operator- (const Vector3& _ref1, const Vector3& _ref2)
{
	return std::move(Vector3((_ref1.X - _ref2.X), (_ref1.Y - _ref2.Y), (_ref1.Z - _ref2.Z)));
}//Vector3 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Vector3 operator* (const Vector3& _ref, const float& _ratio)
{
	return std::move(Vector3(_ref.X*_ratio, _ref.Y*_ratio, _ref.Z*_ratio));
}//Vector3 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Vector3 operator* (const float& _ratio, const Vector3& _ref)
{
	return std::move(Vector3(_ref.X * _ratio, _ref.Y * _ratio, _ref.Z * _ratio));
}//Vector3 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)