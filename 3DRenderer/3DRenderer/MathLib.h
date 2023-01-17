#pragma once
#include <Windows.h>
#include "Matrix44.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "LineFunction2D.h"

struct Plane;

namespace MathLib
{
	template<class T> requires std::is_fundamental_v<T>
	FORCEINLINE constexpr T Clamp(const T X, const T Min, const T Max)
	{
		return X < Min ? Min : X < Max ? X : Max;
	};
	//최대값 최소값 사이의 값 세팅
	template<class T>
	FORCEINLINE constexpr void SwapElement(T* _ref1, T* _ref2) noexcept
	{
		T tmp = *_ref1;
		*_ref1 = *_ref2;
		*_ref2 = tmp;
	};
	template<class T> requires std::is_fundamental_v<T>
	FORCEINLINE constexpr T Abs(const T A)
	{
		return (A >= (T)0) ? A : -A;
	};
	template<typename T> requires std::is_fundamental_v<T>
	FORCEINLINE constexpr T Degree360Lerp(const T _In)
	{
		if (_In >= 0)
			return _In < 360 ? _In : _In - 360;
		else
			return _In > -360 ? _In : _In + 360;
	}
	template<typename T> requires std::is_fundamental_v<T>
	FORCEINLINE Vector3 GetVec2Normal(const T& _X, const T& _Y)
	{
		float InvSqrt = 1 / sqrt(_X * _X + _Y * _Y);
		return Vector3(_X * InvSqrt, _Y * InvSqrt, 0.f);
	}
	//템플릿 함수들
	void		CrossProduct(Matrix44* _out, const Matrix44& _ref1, const Matrix44& _ref2);
	Matrix44	CrossProduct(const Matrix44& _ref1, const Matrix44& _ref2);
	void		CrossProduct(Quaternion* _out, const Matrix44& _refMat, const Quaternion& _refQ);
	Quaternion	CrossProduct(const Matrix44& _refMat, const Quaternion& _refQ);
	void		CrossProduct(Vector3* _out, const Vector3& _ref1, const Vector3& _ref2);
	Vector3		CrossProduct(const Vector3& _ref1, const Vector3& _ref2);
	void		CrossProduct_Inv(Quaternion* _out, const Matrix44& _refMat, const Quaternion& _refQ);
	Quaternion	CrossProduct_Inv(const Matrix44& _refMat, const Quaternion& _refQ);
	//외적 관련 함수들
	float		DotProduct(const Vector3& _ref1, const Vector3& _ref2);
	float		DotProduct(const float& _x1, const float& _y1, const float& _x2, const float& _y2);
	float		GetDotProductCostheata(Vector3& _ref1, Vector3& _ref2);
	void		MakeQuaternionRotateMatrix(Matrix44* _Out, const Vector3& _Rotate);
	void		MakeQuaternionRotateMatrix_Inv(Matrix44* _Out, const Vector3& _Rotate);
	//내적관련 함수들
	void		Make2DLinFunction(LineFunction2D* _Out, const Vector3& _vec1, const Vector3& _vec2);
	void		SortByYvalue(Vector3* _out, const std::span<Vector3>& _In);
	void		InitUnitMatrix44(Matrix44* _Out);
	Plane		MakePlane(const Vector3& _ref1, const Vector3& _ref2, const Vector3& _ref3);
	void		MakePlane(Plane* _Out, const Vector3& _ref1, const Vector3& _ref2, const Vector3& _ref3);
	void		MakePlaneWithMat(std::span<Plane>* _Planearr, const Matrix44& _Mat);
	//파이프라인 관련 함수
	float		GetInvSqrt(const float& _ref);
	Quaternion	GetNormal(const Quaternion& _ref);
	//계산 함수
	Vector3		EraseDecimalXY(Vector3& _Vec);
	float		EraseDecimalXY_lifting(const float& _ref);
	float		EraseDecimalXY_falling(const float& _ref);
}
