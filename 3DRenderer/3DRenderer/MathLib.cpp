#include "stdafx.h"
#include <math.h>
#include <span>

namespace MathLib
{
	void MathLib::CrossProduct(Matrix44* _out, const Matrix44& _ref1, const Matrix44& _ref2)
	{
		_out->mat44[0][0] = (_ref1.mat44[0][0] * _ref2.mat44[0][0]) + (_ref1.mat44[0][1] * _ref2.mat44[1][0]) + (_ref1.mat44[0][2] * _ref2.mat44[2][0]) + (_ref1.mat44[0][3] * _ref2.mat44[3][0]);
		_out->mat44[0][1] = (_ref1.mat44[0][0] * _ref2.mat44[0][1]) + (_ref1.mat44[0][1] * _ref2.mat44[1][1]) + (_ref1.mat44[0][2] * _ref2.mat44[2][1]) + (_ref1.mat44[0][3] * _ref2.mat44[3][1]);
		_out->mat44[0][2] = (_ref1.mat44[0][0] * _ref2.mat44[0][2]) + (_ref1.mat44[0][1] * _ref2.mat44[1][2]) + (_ref1.mat44[0][2] * _ref2.mat44[2][2]) + (_ref1.mat44[0][3] * _ref2.mat44[3][2]);
		_out->mat44[0][3] = (_ref1.mat44[0][0] * _ref2.mat44[0][3]) + (_ref1.mat44[0][1] * _ref2.mat44[1][3]) + (_ref1.mat44[0][2] * _ref2.mat44[2][3]) + (_ref1.mat44[0][3] * _ref2.mat44[3][3]);

		_out->mat44[1][0] = (_ref1.mat44[1][0] * _ref2.mat44[0][0]) + (_ref1.mat44[1][1] * _ref2.mat44[1][0]) + (_ref1.mat44[1][2] * _ref2.mat44[2][0]) + (_ref1.mat44[1][3] * _ref2.mat44[3][0]);
		_out->mat44[1][1] = (_ref1.mat44[1][0] * _ref2.mat44[0][1]) + (_ref1.mat44[1][1] * _ref2.mat44[1][1]) + (_ref1.mat44[1][2] * _ref2.mat44[2][1]) + (_ref1.mat44[1][3] * _ref2.mat44[3][1]);
		_out->mat44[1][2] = (_ref1.mat44[1][0] * _ref2.mat44[0][2]) + (_ref1.mat44[1][1] * _ref2.mat44[1][2]) + (_ref1.mat44[1][2] * _ref2.mat44[2][2]) + (_ref1.mat44[1][3] * _ref2.mat44[3][2]);
		_out->mat44[1][3] = (_ref1.mat44[1][0] * _ref2.mat44[0][3]) + (_ref1.mat44[1][1] * _ref2.mat44[1][3]) + (_ref1.mat44[1][2] * _ref2.mat44[2][3]) + (_ref1.mat44[1][3] * _ref2.mat44[3][3]);

		_out->mat44[2][0] = (_ref1.mat44[2][0] * _ref2.mat44[0][0]) + (_ref1.mat44[2][1] * _ref2.mat44[1][0]) + (_ref1.mat44[2][2] * _ref2.mat44[2][0]) + (_ref1.mat44[2][3] * _ref2.mat44[3][0]);
		_out->mat44[2][1] = (_ref1.mat44[2][0] * _ref2.mat44[0][1]) + (_ref1.mat44[2][1] * _ref2.mat44[1][1]) + (_ref1.mat44[2][2] * _ref2.mat44[2][1]) + (_ref1.mat44[2][3] * _ref2.mat44[3][1]);
		_out->mat44[2][2] = (_ref1.mat44[2][0] * _ref2.mat44[0][2]) + (_ref1.mat44[2][1] * _ref2.mat44[1][2]) + (_ref1.mat44[2][2] * _ref2.mat44[2][2]) + (_ref1.mat44[2][3] * _ref2.mat44[3][2]);
		_out->mat44[2][3] = (_ref1.mat44[2][0] * _ref2.mat44[0][3]) + (_ref1.mat44[2][1] * _ref2.mat44[1][3]) + (_ref1.mat44[2][2] * _ref2.mat44[2][3]) + (_ref1.mat44[2][3] * _ref2.mat44[3][3]);

		_out->mat44[3][0] = (_ref1.mat44[3][0] * _ref2.mat44[0][0]) + (_ref1.mat44[3][1] * _ref2.mat44[1][0]) + (_ref1.mat44[3][2] * _ref2.mat44[2][0]) + (_ref1.mat44[3][3] * _ref2.mat44[3][0]);
		_out->mat44[3][1] = (_ref1.mat44[3][0] * _ref2.mat44[0][1]) + (_ref1.mat44[3][1] * _ref2.mat44[1][1]) + (_ref1.mat44[3][2] * _ref2.mat44[2][1]) + (_ref1.mat44[3][3] * _ref2.mat44[3][1]);
		_out->mat44[3][2] = (_ref1.mat44[3][0] * _ref2.mat44[0][2]) + (_ref1.mat44[3][1] * _ref2.mat44[1][2]) + (_ref1.mat44[3][2] * _ref2.mat44[2][2]) + (_ref1.mat44[3][3] * _ref2.mat44[3][2]);
		_out->mat44[3][3] = (_ref1.mat44[3][0] * _ref2.mat44[0][3]) + (_ref1.mat44[3][1] * _ref2.mat44[1][3]) + (_ref1.mat44[3][2] * _ref2.mat44[2][3]) + (_ref1.mat44[3][3] * _ref2.mat44[3][3]);

	};
	Matrix44 MathLib::CrossProduct(const Matrix44& _ref1, const Matrix44& _ref2)
	{
		Matrix44 result;
		result.mat44[0][0] = (_ref1.mat44[0][0] * _ref2.mat44[0][0]) + (_ref1.mat44[0][1] * _ref2.mat44[1][0]) + (_ref1.mat44[0][2] * _ref2.mat44[2][0]) + (_ref1.mat44[0][3] * _ref2.mat44[3][0]);
		result.mat44[0][1] = (_ref1.mat44[0][0] * _ref2.mat44[0][1]) + (_ref1.mat44[0][1] * _ref2.mat44[1][1]) + (_ref1.mat44[0][2] * _ref2.mat44[2][1]) + (_ref1.mat44[0][3] * _ref2.mat44[3][1]);
		result.mat44[0][2] = (_ref1.mat44[0][0] * _ref2.mat44[0][2]) + (_ref1.mat44[0][1] * _ref2.mat44[1][2]) + (_ref1.mat44[0][2] * _ref2.mat44[2][2]) + (_ref1.mat44[0][3] * _ref2.mat44[3][2]);
		result.mat44[0][3] = (_ref1.mat44[0][0] * _ref2.mat44[0][3]) + (_ref1.mat44[0][1] * _ref2.mat44[1][3]) + (_ref1.mat44[0][2] * _ref2.mat44[2][3]) + (_ref1.mat44[0][3] * _ref2.mat44[3][3]);

		result.mat44[1][0] = (_ref1.mat44[1][0] * _ref2.mat44[0][0]) + (_ref1.mat44[1][1] * _ref2.mat44[1][0]) + (_ref1.mat44[1][2] * _ref2.mat44[2][0]) + (_ref1.mat44[1][3] * _ref2.mat44[3][0]);
		result.mat44[1][1] = (_ref1.mat44[1][0] * _ref2.mat44[0][1]) + (_ref1.mat44[1][1] * _ref2.mat44[1][1]) + (_ref1.mat44[1][2] * _ref2.mat44[2][1]) + (_ref1.mat44[1][3] * _ref2.mat44[3][1]);
		result.mat44[1][2] = (_ref1.mat44[1][0] * _ref2.mat44[0][2]) + (_ref1.mat44[1][1] * _ref2.mat44[1][2]) + (_ref1.mat44[1][2] * _ref2.mat44[2][2]) + (_ref1.mat44[1][3] * _ref2.mat44[3][2]);
		result.mat44[1][3] = (_ref1.mat44[1][0] * _ref2.mat44[0][3]) + (_ref1.mat44[1][1] * _ref2.mat44[1][3]) + (_ref1.mat44[1][2] * _ref2.mat44[2][3]) + (_ref1.mat44[1][3] * _ref2.mat44[3][3]);

		result.mat44[2][0] = (_ref1.mat44[2][0] * _ref2.mat44[0][0]) + (_ref1.mat44[2][1] * _ref2.mat44[1][0]) + (_ref1.mat44[2][2] * _ref2.mat44[2][0]) + (_ref1.mat44[2][3] * _ref2.mat44[3][0]);
		result.mat44[2][1] = (_ref1.mat44[2][0] * _ref2.mat44[0][1]) + (_ref1.mat44[2][1] * _ref2.mat44[1][1]) + (_ref1.mat44[2][2] * _ref2.mat44[2][1]) + (_ref1.mat44[2][3] * _ref2.mat44[3][1]);
		result.mat44[2][2] = (_ref1.mat44[2][0] * _ref2.mat44[0][2]) + (_ref1.mat44[2][1] * _ref2.mat44[1][2]) + (_ref1.mat44[2][2] * _ref2.mat44[2][2]) + (_ref1.mat44[2][3] * _ref2.mat44[3][2]);
		result.mat44[2][3] = (_ref1.mat44[2][0] * _ref2.mat44[0][3]) + (_ref1.mat44[2][1] * _ref2.mat44[1][3]) + (_ref1.mat44[2][2] * _ref2.mat44[2][3]) + (_ref1.mat44[2][3] * _ref2.mat44[3][3]);

		result.mat44[3][0] = (_ref1.mat44[3][0] * _ref2.mat44[0][0]) + (_ref1.mat44[3][1] * _ref2.mat44[1][0]) + (_ref1.mat44[3][2] * _ref2.mat44[2][0]) + (_ref1.mat44[3][3] * _ref2.mat44[3][0]);
		result.mat44[3][1] = (_ref1.mat44[3][0] * _ref2.mat44[0][1]) + (_ref1.mat44[3][1] * _ref2.mat44[1][1]) + (_ref1.mat44[3][2] * _ref2.mat44[2][1]) + (_ref1.mat44[3][3] * _ref2.mat44[3][1]);
		result.mat44[3][2] = (_ref1.mat44[3][0] * _ref2.mat44[0][2]) + (_ref1.mat44[3][1] * _ref2.mat44[1][2]) + (_ref1.mat44[3][2] * _ref2.mat44[2][2]) + (_ref1.mat44[3][3] * _ref2.mat44[3][2]);
		result.mat44[3][3] = (_ref1.mat44[3][0] * _ref2.mat44[0][3]) + (_ref1.mat44[3][1] * _ref2.mat44[1][3]) + (_ref1.mat44[3][2] * _ref2.mat44[2][3]) + (_ref1.mat44[3][3] * _ref2.mat44[3][3]);
		return result;
	};
	void MathLib::CrossProduct(Quaternion* _out, const Matrix44& _refMat, const Quaternion& _refQ)
	{
		_out->X = (_refQ.X * _refMat.mat44[0][0]) + (_refQ.Y * _refMat.mat44[1][0]) + (_refQ.Z * _refMat.mat44[2][0]) + (_refQ.W * _refMat.mat44[3][0]);
		_out->Y = (_refQ.X * _refMat.mat44[0][1]) + (_refQ.Y * _refMat.mat44[1][1]) + (_refQ.Z * _refMat.mat44[2][1]) + (_refQ.W * _refMat.mat44[3][1]);
		_out->Z = (_refQ.X * _refMat.mat44[0][2]) + (_refQ.Y * _refMat.mat44[1][2]) + (_refQ.Z * _refMat.mat44[2][2]) + (_refQ.W * _refMat.mat44[3][2]);
		_out->W = (_refQ.X * _refMat.mat44[0][3]) + (_refQ.Y * _refMat.mat44[1][3]) + (_refQ.Z * _refMat.mat44[2][3]) + (_refQ.W * _refMat.mat44[3][3]);
	};
	Quaternion MathLib::CrossProduct(const Matrix44& _refMat, const Quaternion& _refQ)
	{
		return std::move(Quaternion(
			((_refQ.X * _refMat.mat44[0][0]) + (_refQ.Y * _refMat.mat44[1][0]) + (_refQ.Z * _refMat.mat44[2][0]) + (_refQ.W * _refMat.mat44[3][0]))
			, ((_refQ.X * _refMat.mat44[0][1]) + (_refQ.Y * _refMat.mat44[1][1]) + (_refQ.Z * _refMat.mat44[2][1]) + (_refQ.W * _refMat.mat44[3][1]))
			, ((_refQ.X * _refMat.mat44[0][2]) + (_refQ.Y * _refMat.mat44[1][2]) + (_refQ.Z * _refMat.mat44[2][2]) + (_refQ.W * _refMat.mat44[3][2]))
			, ((_refQ.X * _refMat.mat44[0][3]) + (_refQ.Y * _refMat.mat44[1][3]) + (_refQ.Z * _refMat.mat44[2][3]) + (_refQ.W * _refMat.mat44[3][3]))));

	};
	void MathLib::CrossProduct(Vector3* _out, const Vector3& _ref1, const Vector3& _ref2)
	{
		_out->X = (_ref1.Y * _ref2.Z) - (_ref1.Z * _ref2.Y);
		_out->Y = (_ref1.Z * _ref2.X) - (_ref1.X * _ref2.Z);
		_out->Z = (_ref1.X * _ref2.Y) - (_ref1.Y * _ref2.X);
	};
	Vector3 MathLib::CrossProduct(const Vector3& _ref1, const Vector3& _ref2)
	{
		return std::move(Vector3(
			((_ref1.Y * _ref2.Z) - (_ref1.Z * _ref2.Y))
			, ((_ref1.Z * _ref2.X) - (_ref1.X * _ref2.Z))
			, ((_ref1.X * _ref2.Y) - (_ref1.Y * _ref2.X))));
	};
	float MathLib::DotProduct(const Vector3& _ref1, const Vector3& _ref2)
	{
		return std::move(((_ref1.X * _ref2.X) + (_ref1.Y * _ref2.Y) + (_ref1.Z * _ref2.Z)));
	};
	float DotProduct(const float& _x1, const float& _y1, const float& _x2, const float& _y2)
	{
		return std::move(_x1*_x2 + _y1*_y2);
	};
	float MathLib::GetDotProductCostheata(Vector3& _ref1, Vector3& _ref2)
	{
		return std::move(acos((DotProduct(_ref1, _ref2)) / (_ref1.GetVectorLength() * _ref2.GetVectorLength())));
	};
	void MathLib::MakeQuaternionRotateMatrix(Matrix44* _Out, const Vector3& _Rotate)
	{
		//Z와 Y의 회전값 적용 위치 변경, Z->Y, Y->Z, UpVector가 Z축이 되도록 함 : 입력값을 Y와 Z값을 변경하여 받음(내부계산식은 동일)
		//yaw = y, pitch = x, roll = z;
		float Yaw = _Rotate.Y, Pitch = _Rotate.X, Roll = _Rotate.Z;
		float CosR = cos(Roll / 2), CosP = cos(Pitch / 2), CosY = cos(Yaw / 2);
		float SinR = sin(Roll / 2), SinP = sin(Pitch / 2), SinY = sin(Yaw / 2);

		float W = CosR * CosP * CosY + SinR * SinP * SinY;
		float X = CosR * SinP * CosY + SinR * CosP * SinY;
		float Y = CosR * CosP * SinY - SinR * SinP * CosY;
		float Z = SinR * CosP * CosY - CosR * SinP * SinY;
		
		_Out->mat44[0][0] = 1 - (2 * Y * Y) - (2 * Z * Z); // 1 - (2 * Y * Y) - (2 * X * X);
		_Out->mat44[0][1] = 2 * X * Y - 2 * W * Z;
		_Out->mat44[0][2] = 2 * X * Z + 2 * W * Y;
		_Out->mat44[0][3] = 0;

		_Out->mat44[1][0] = 2 * X * Y + 2 * W * Z;
		_Out->mat44[1][1] = 1 - (2 * X * X) - (2 * Z * Z);
		_Out->mat44[1][2] = 2 * Y * Z - 2 * W * X;
		_Out->mat44[1][3] = 0;

		_Out->mat44[2][0] = 2 * X * Z - 2 * W * Y;
		_Out->mat44[2][1] = 2 * Y * Z + 2 * W * X;
		_Out->mat44[2][2] = 1 - (2 * X * X) - (2 * Y * Y);
		_Out->mat44[2][3] = 0;

		_Out->mat44[3][0] = 0;
		_Out->mat44[3][1] = 0;
		_Out->mat44[3][2] = 0;
		_Out->mat44[3][3] = 1;
		//책에서는 행렬 연산의 행렬이 바뀌어 있으므로 공식은 프로그램에 맞춰 수정(위는 원래 책의 공식)

		/*
		_Out->mat44[0][0] = 1 - (2 * Y * Y) - (2 * Z * Z); // 1 - (2 * Y * Y) - (2 * X * X);
		_Out->mat44[0][1] = 2 * X * Y + 2 * W * Z;
		_Out->mat44[0][2] = 2 * X * Z - 2 * W * Y;
		_Out->mat44[0][3] = 0;

		_Out->mat44[1][0] = 2 * X * Y - 2 * W * Z;
		_Out->mat44[1][1] = 1 - (2 * X * X) - (2 * Z * Z);
		_Out->mat44[1][2] = 2 * Y * Z + 2 * W * X;
		_Out->mat44[1][3] = 0;

		_Out->mat44[2][0] = 2 * X * Z + 2 * W * Y;
		_Out->mat44[2][1] = 2 * Y * Z - 2 * W * X;
		_Out->mat44[2][2] = 1 - (2 * X * X) - (2 * Y * Y);
		_Out->mat44[2][3] = 0;

		_Out->mat44[3][0] = 0;
		_Out->mat44[3][1] = 0;
		_Out->mat44[3][2] = 0;
		_Out->mat44[3][3] = 1;		
		*/
	};
	void MathLib::Make2DLinFunction(LineFunction2D* _Out, const Vector3& _vec1, const Vector3& _vec2)
	{
		float DeltaX(_vec1.X - _vec2.X), DeltaY( _vec1.Y - _vec2.Y);

		if (DeltaX == 0)
		{
			_Out->XSlopeZero = true;
			return;
		}
		else if (DeltaY == 0)
		{
			_Out->YSlopeZero = true;
			return;
		}

		_Out->Slope = DeltaY / DeltaX;
		_Out->Constant = _vec1.Y - _Out->Slope * _vec1.X;
	};
	void MathLib::SortByYvalue(Vector3* _out, const std::span<Vector3>& _In)
	{
		Vector3 tmp[]{_In[0], _In[1], _In[2]};	

		int i = _In.size() - 1, j = 0;
		while (i != 0)
		{
			if (j == i)
			{
				j = 0; i--;
			}

			if (tmp[j].Y > tmp[j + 1].Y)
				SwapElement(&tmp[j], &tmp[j + 1]);

			j++;
		}

		for (int i = 0; i < _In.size(); i++)
			_out[i] = tmp[i];
	};
	void MathLib::InitUnitMatrix44(Matrix44* _Out)
	{
		memset(_Out, 0, sizeof(Matrix44));
		_Out->mat44[0][0] = 1.f;
		_Out->mat44[1][1] = 1.f;
		_Out->mat44[2][2] = 1.f;
		_Out->mat44[3][3] = 1.f;
	};
	Plane MathLib::MakePlane(const Vector3& _ref1, const Vector3& _ref2, const Vector3& _ref3)
	{
		Vector3 tmp1(_ref2.X - _ref1.X, _ref2.Y - _ref1.Y, _ref2.Z - _ref1.Z);
		Vector3 tmp2(_ref3.X - _ref1.X, _ref3.Y - _ref1.Y, _ref3.Z - _ref1.Z);
		tmp1 = CrossProduct(tmp1, tmp2);
		float D = tmp1.X * _ref1.X + tmp1.Y * _ref1.Y + tmp1.Z * _ref1.Z;

		return std::move(Plane(tmp1.X, tmp1.Y, tmp1.Z, D));
	};
	void MathLib::MakePlane(Plane* _Out, const Vector3& _ref1, const Vector3& _ref2, const Vector3& _ref3)
	{
		Vector3 tmp1(_ref2.X - _ref1.X, _ref2.Y - _ref1.Y, _ref2.Z - _ref1.Z);
		Vector3 tmp2(_ref3.X - _ref1.X, _ref3.Y - _ref1.Y, _ref3.Z - _ref1.Z);
		tmp1 = CrossProduct(tmp1, tmp2);
		float D = tmp1.X * _ref1.X + tmp1.Y * _ref1.Y + tmp1.Z * _ref1.Z;

		_Out->a = tmp1.X; _Out->b = tmp1.Y; _Out->c = tmp1.Z; _Out->d = D;
	};
	void MathLib::MakePlaneWithMat(std::span<Plane>* _Planearr, const Matrix44& _Mat)
	{
		if (_Planearr == nullptr || _Planearr->size() != 6)
			return;

		int i(0);
		for (auto iter = _Planearr->begin(); iter != _Planearr->end(); i++)
		{
			//+x,-x,+y,-y,+z,-z 순으로 생성
			iter->a = -(_Mat.mat44[0][3] + _Mat.mat44[0][i]);
			iter->b = -(_Mat.mat44[1][3] + _Mat.mat44[1][i]);
			iter->c = -(_Mat.mat44[2][3] + _Mat.mat44[2][i]);
			iter->d = -(_Mat.mat44[3][3] + _Mat.mat44[3][i]);
			iter++;

			iter->a = -(_Mat.mat44[0][3] - _Mat.mat44[0][i]);
			iter->b = -(_Mat.mat44[1][3] - _Mat.mat44[1][i]);
			iter->c = -(_Mat.mat44[2][3] - _Mat.mat44[2][i]);
			iter->d = -(_Mat.mat44[3][3] - _Mat.mat44[3][i]);
			iter++;
		}
	};
	float MathLib::GetInvSqrt(const float& _ref)
	{
		// Performs two passes of Newton-Raphson iteration on the hardware estimate
		//    v^-0.5 = x
		// => x^2 = v^-1
		// => 1/(x^2) = v
		// => F(x) = x^-2 - v
		//    F'(x) = -2x^-3

		//    x1 = x0 - F(x0)/F'(x0)
		// => x1 = x0 + 0.5 * (x0^-2 - Vec) * x0^3
		// => x1 = x0 + 0.5 * (x0 - Vec * x0^3)
		// => x1 = x0 + x0 * (0.5 - 0.5 * Vec * x0^2)
		//
		// This final form has one more operation than the legacy factorization (X1 = 0.5*X0*(3-(Y*X0)*X0)
		// but retains better accuracy (namely InvSqrt(1) = 1 exactly).

		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float temp;

		Y0 = _mm_set_ss(_ref);
		X0 = _mm_rsqrt_ss(Y0);	// 1/sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		// 2nd Newton-Raphson iteration
		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&temp, X2);
		return temp;
	};//고속 역제곱근 공식 => 1/루트(x)의 값을 넘겨줌
	Quaternion MathLib::GetNormal(const Quaternion& _ref)
	{
		float SrqSz = _ref.X * _ref.X + _ref.Y * _ref.Y + _ref.Z * _ref.Z;
		SrqSz = GetInvSqrt(SrqSz);
		
		return std::move(Quaternion(_ref.X * SrqSz, _ref.Y * SrqSz, _ref.Z * SrqSz, _ref.W));
	}
	Vector3 EraseDecimalXY(Vector3& _Vec)
	{
		float tmp;
		Vector3 tmpVec;

		tmpVec.X = (int)_Vec.X;
		tmp = _Vec.X - tmpVec.X;
		if (tmp > 0.5f)
			tmpVec.X = tmpVec.X + 1;	

		tmpVec.Y = (int)_Vec.Y;
		tmp = _Vec.Y - tmpVec.Y;
		if (tmp > 0.5f)
			tmpVec.Y = tmpVec.Y + 1;

		return std::move(tmpVec);
	};
};