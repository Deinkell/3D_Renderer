#pragma once
#include "MathLib.h"
#include "Vector3.h"

struct Quaternion
{
public:
	float X, Y, Z, W;
	
public:
	FORCEINLINE constexpr Quaternion() : X(0.f), Y(0.f), Z(0.f), W(0.f) {};
	FORCEINLINE constexpr Quaternion(const Vector3& _ref) : X(_ref.X), Y(_ref.Y), Z(_ref.Z), W(1.f) {};
	FORCEINLINE Quaternion(const float& _x, const float& _y, const float& _z, const float& _w) 
	: X(_x), Y(_y), Z(_z), W(_w) {};
	FORCEINLINE Quaternion(float&& _x, float&& _y, float&& _z, float&& _w)
	: X(std::move(_x)), Y(std::move(_y)), Z(std::move(_z)), W(std::move(_w)) {};
	template<typename T> requires std::is_same<Quaternion, T>::value
	FORCEINLINE Quaternion(T&& _ref) noexcept
	: X(std::forward<float>(_ref.X)), Y(std::forward<float>(_ref.Y)), Z(std::forward<float>(_ref.Z)), W(std::forward<float>(_ref.W))
	{};
	//완벽전달 복사생성자(복사생성, 이동복사생성)
	~Quaternion() = default;
	//소멸자

public:
	template<typename T> requires std::is_same<Quaternion, T>::value
	FORCEINLINE T& operator= (T&& _ref) noexcept
	{
		if (this == &_ref)
			return *this;

		X = std::forward<float>(_ref.X);
		Y = std::forward<float>(_ref.Y);
		Z = std::forward<float>(_ref.Z);
		W = std::forward<float>(_ref.W);

		return *this;
	}
	FORCEINLINE constexpr void operator+=(const Quaternion& _ref);
	FORCEINLINE constexpr bool operator==(const Quaternion& _ref);

public:
	FORCEINLINE Quaternion GetQuaternion() { return std::move(Quaternion(X, Y, Z, W)); };
	Quaternion GetNormal(); 
};

FORCEINLINE constexpr void Quaternion::operator+=(const Quaternion& _ref)
{
	X += _ref.X;
	Y += _ref.Y;
	Z += _ref.Z;
	W += _ref.W;
}

FORCEINLINE constexpr bool Quaternion::operator==(const Quaternion& _ref)
{
	return !(X == _ref.X) ? false : !(Y == _ref.Y) ? false : !(Z == _ref.Z) ? false : !(W == _ref.W) ? false : true;
}

////////////////Quaternion global operator/////////////////
FORCEINLINE Quaternion operator+(const Quaternion& _ref1, const Quaternion& _ref2)
{
	return std::move(Quaternion((_ref1.X + _ref2.X), (_ref1.Y + _ref2.Y), (_ref1.Z + _ref2.Z), (_ref1.W + _ref2.W)));
}//Quaternion 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE  Quaternion operator-(const Quaternion& _ref1, const Quaternion& _ref2)
{
	return std::move(Quaternion((_ref1.X - _ref2.X), (_ref1.Y - _ref2.Y), (_ref1.Z - _ref2.Z), (_ref1.W - _ref2.W)));
}//Quaternion 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)
FORCEINLINE Quaternion operator* (const Quaternion& _ref, const float& _ratio)
{
	return std::move(Quaternion(_ref.X * _ratio, _ref.Y * _ratio, _ref.Z * _ratio, _ref.W * _ratio));
}//Quaternion 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Quaternion operator* (const float& _ratio, const Quaternion& _ref)
{
	return std::move(Quaternion(_ref.X * _ratio, _ref.Y * _ratio, _ref.Z * _ratio, _ref.W * _ratio));
}//Quaternion 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)
