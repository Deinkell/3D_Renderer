#pragma once
#include <iostream>
#include <memory.h>
#include "MathLib.h"

struct Vector3
{
public:
	float X, Y, Z;

public:
	constexpr Vector3() : X(0.f), Y(0.f), Z(0.f) {};
	Vector3(const float& _x, const float& _y, const float& _z) : X(_x), Y(_y), Z(_z) {};
	Vector3(float&& _x, float&& _y, float&& _z)
	: X(std::move(_x)), Y(std::move(_y)), Z(std::move(_z)) {};
	template<typename T> requires std::is_same<Vector3, T>::value
	Vector3(T&& _ref)
	: X(std::forward<float>(_ref.X)), Y(std::forward<float>(_ref.Y)), Z(std::forward<float>(_ref.Z)) {};
	//완벽전달 생성자

public:
	template<typename T> requires std::is_same<Vector3, T>::value
	FORCEINLINE T& operator=(T&& _ref) noexcept
	{
		if (this == &_ref)
			return *this;

		X = std::forward<float>(_ref.X);
		Y = std::forward<float>(_ref.Y);
		Z = std::forward<float>(_ref.Z);

		return *this;
	};

	FORCEINLINE constexpr void operator+= (const Vector3& _ref);
	FORCEINLINE constexpr bool operator==(const Vector3& _ref);
	~Vector3() = default;

public:
	Vector3 GetVec3() { return std::move(Vector3(X, Y, Z)); };
	FORCEINLINE Vector3 GetNormalVector();
	FORCEINLINE float GetVectorLength() { return std::move((float)sqrt((X * X) + (Y * Y) + (Z * Z)));}
	FORCEINLINE float GetVectorSquredSize() { return std::move(X * X + Y * Y + Z * Z); }
};


//Vector3 연산관련 오퍼레이터
FORCEINLINE constexpr void Vector3::operator+= (const Vector3& _ref)
{
	X += _ref.X;
	Y += _ref.Y;
	Z += _ref.Z;
};
//Vector3 연산관련 오퍼레이터
FORCEINLINE constexpr bool Vector3::operator==(const Vector3& _ref)
{
	return !(X == _ref.X) ? false : !(Y == _ref.Y) ? false : !(Z == _ref.Z) ? false : true;
};
FORCEINLINE Vector3 Vector3::GetNormalVector()
{
	float size = std::move(sqrt(X * X + Y * Y + Z * Z));
	
	if (size == 0)
		return std::move(Vector3());

	return std::move(Vector3((X / size), (Y / size), (Z / size)));
};

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
	return std::move(Vector3(_ref.X * _ratio, _ref.Y * _ratio, _ref.Z * _ratio));
}//Vector3 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Vector3 operator* (const float& _ratio, const Vector3& _ref)
{
	return std::move(Vector3(_ref.X * _ratio, _ref.Y * _ratio, _ref.Z * _ratio));
}//Vector3 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)
