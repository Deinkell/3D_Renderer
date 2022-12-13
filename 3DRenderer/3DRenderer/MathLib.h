#pragma once
#include <Windows.h>
#include "Matrix44.h"
#include "Quaternion.h"
#include "Vector3.h"

namespace MathLib
{
	template<class T> requires std::is_fundamental_v<T>
	FORCEINLINE constexpr T Clamp(const T X, const T Min, const T Max)
	{
		return X < Min ? Min : X < Max ? X : Max;
	};
	//최대값 최소값 사이의 값 세팅
	void		CrossProduct(Matrix44* _out, const Matrix44& _ref1, const Matrix44& _ref2);
	Matrix44	CrossProduct(const Matrix44& _ref1, const Matrix44& _ref2);
	void		CrossProduct(Quaternion* _out, const Matrix44& _refMat, const Quaternion& _refQ);
	Quaternion	CrossProduct(const Matrix44& _refMat, const Quaternion& _refQ);
	void		CrossProduct(Vector3* _out, const Vector3& _ref1, const Vector3& _ref2);
	Vector3		CrossProduct(const Vector3& _ref1, const Vector3& _ref2);
	//외적 관련 함수들
	float		DotProduct(const Vector3& _ref1, const Vector3& _ref2);
	float		GetDotProductCostheata(Vector3& _ref1, Vector3& _ref2);
	void		MakeQuaternionRotateMatrix(Matrix44* _Out, const Vector3& _Rotate);
	//내적관련 함수들
};
