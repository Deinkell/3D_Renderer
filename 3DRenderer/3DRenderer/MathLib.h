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
	//�ִ밪 �ּҰ� ������ �� ����
	FORCEINLINE void CrossProduct(Matrix44* _out, const Matrix44& _ref1, const Matrix44& _ref2);
	FORCEINLINE Matrix44 CrossProduct(const Matrix44& _ref1, const Matrix44& _ref2);
	FORCEINLINE void CrossProduct(Quaternion* _out, const Matrix44& _refMat, const Quaternion& _refQ);
	FORCEINLINE Quaternion CrossProduct(const Matrix44& _refMat, const Quaternion& _refQ);
	FORCEINLINE void CrossProduct(Vector3* _out, const Vector3& _ref1, const Vector3& _ref2);
	FORCEINLINE Vector3 CrossProduct(const Vector3& _ref1, const Vector3& _ref2);
	//���� ���� �Լ���
	FORCEINLINE float DotProduct(const Vector3& _ref1, const Vector3& _ref2);
	FORCEINLINE float GetDotProductCostheata(Vector3& _ref1, Vector3& _ref2);
	//�������� �Լ���
};
