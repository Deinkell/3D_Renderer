#include "stdafx.h"
#include <math.h>
#include "MathLib.h"

namespace MathLib
{
	FORCEINLINE void CrossProduct(Matrix44* _out, const Matrix44& _ref1, const Matrix44& _ref2)
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

	FORCEINLINE Matrix44 CrossProduct(const Matrix44& _ref1, const Matrix44& _ref2)
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

	FORCEINLINE void CrossProduct(Quaternion* _out, const Matrix44& _refMat, const Quaternion& _refQ)
	{
		_out->X = (_refQ.X * _refMat.mat44[0][0]) + (_refQ.Y * _refMat.mat44[1][0]) + (_refQ.Z * _refMat.mat44[2][0]) + (_refQ.W * _refMat.mat44[3][0]);
		_out->Y = (_refQ.X * _refMat.mat44[0][1]) + (_refQ.Y * _refMat.mat44[1][1]) + (_refQ.Z * _refMat.mat44[2][1]) + (_refQ.W * _refMat.mat44[3][1]);
		_out->Z = (_refQ.X * _refMat.mat44[0][2]) + (_refQ.Y * _refMat.mat44[1][2]) + (_refQ.Z * _refMat.mat44[2][2]) + (_refQ.W * _refMat.mat44[3][2]);
		_out->W = (_refQ.X * _refMat.mat44[0][3]) + (_refQ.Y * _refMat.mat44[1][3]) + (_refQ.Z * _refMat.mat44[2][3]) + (_refQ.W * _refMat.mat44[3][3]);
	};

	FORCEINLINE Quaternion CrossProduct(const Matrix44& _refMat, const Quaternion& _refQ)
	{
		return std::move(Quaternion(
			((_refQ.X * _refMat.mat44[0][0]) + (_refQ.Y * _refMat.mat44[1][0]) + (_refQ.Z * _refMat.mat44[2][0]) + (_refQ.W * _refMat.mat44[3][0]))
			, ((_refQ.X * _refMat.mat44[0][1]) + (_refQ.Y * _refMat.mat44[1][1]) + (_refQ.Z * _refMat.mat44[2][1]) + (_refQ.W * _refMat.mat44[3][1]))
			, ((_refQ.X * _refMat.mat44[0][2]) + (_refQ.Y * _refMat.mat44[1][2]) + (_refQ.Z * _refMat.mat44[2][2]) + (_refQ.W * _refMat.mat44[3][2]))
			, ((_refQ.X * _refMat.mat44[0][3]) + (_refQ.Y * _refMat.mat44[1][3]) + (_refQ.Z * _refMat.mat44[2][3]) + (_refQ.W * _refMat.mat44[3][3]))));

	};

	FORCEINLINE void CrossProduct(Vector3* _out, const Vector3& _ref1, const Vector3& _ref2)
	{
		_out->X = (_ref1.Y * _ref2.Z) - (_ref1.Z * _ref2.Y);
		_out->Y = (_ref1.Z * _ref2.X) - (_ref1.X * _ref2.Z);
		_out->Z = (_ref1.X * _ref2.Y) - (_ref1.Y * _ref2.X);
	};

	FORCEINLINE Vector3 CrossProduct(const Vector3& _ref1, const Vector3& _ref2)
	{
		return std::move(Vector3(
			((_ref1.Y * _ref2.Z) - (_ref1.Z * _ref2.Y))
			, ((_ref1.Z * _ref2.X) - (_ref1.X * _ref2.Z))
			, ((_ref1.X * _ref2.Y) - (_ref1.Y * _ref2.X))));
	};
	FORCEINLINE float DotProduct(const Vector3& _ref1, const Vector3& _ref2)
	{
		return ((_ref1.X * _ref2.X) + (_ref1.Y * _ref2.Y) + (_ref1.Z * _ref2.Z));
	};

	FORCEINLINE float GetDotProductCostheata(Vector3& _ref1, Vector3& _ref2)
	{
		return acos((DotProduct(_ref1, _ref2)) / (_ref1.GetVectorLength() * _ref2.GetVectorLength()));
	};
}