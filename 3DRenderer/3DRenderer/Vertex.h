#pragma once

#include "MathLib.h"
#include "Vector3.h"
#include "Color32.h"
#include "LinearColor.h"

struct Vertex
{
public:
	Quaternion Pos;
	LinearColor Color;
	Vector3 NormalVec;
	float U = 0.f, V = 0.f;

public:
	Vertex() = default;
	FORCEINLINE constexpr Vertex(const Quaternion& _Pos, const LinearColor& _Color, const Vector3& _Normal, const float _U, const float _V)
	: Pos(_Pos), Color(_Color), NormalVec(_Normal), U(_U), V(_V){};
	FORCEINLINE Vertex(Quaternion&& _Pos, LinearColor&& _Color, Vector3& _Normal, float&& _U, float&& _V)
	: Pos(std::move(_Pos)), Color(std::move(_Color)), NormalVec(std::move(_Normal)), U(std::move(_U)), V(std::move(_V)) {};
	FORCEINLINE constexpr Vertex(const Vertex& _ref) : Pos(_ref.Pos), Color(_ref.Color), NormalVec(_ref.NormalVec), U(_ref.U), V(_ref.V){};
	~Vertex() = default;

public:
	template<typename T> requires std::is_same_v<Vertex, T>
	FORCEINLINE Vertex operator=(T&& _ref) noexcept
	{
		if (this == &_ref)
			return *this;

		Pos = std::forward<Quaternion>((Quaternion)_ref.Pos);
		Color = std::forward<LinearColor>((LinearColor)_ref.Color);
		NormalVec = std::forward<Vector3>((Vector3)_ref.NormalVec);
		U = std::forward<float>(_ref.U);
		V = std::forward<float>(_ref.V);

		return *this;
	}
	

public:
	FORCEINLINE Vector3 GetNormalVec() { return NormalVec; }
	void SetNormalVec();

public:
	void MakeRenderdata(const Matrix44& _FMat, const Matrix44& _WrdViewMat);
	void MakeRenderdata_Inv(const Matrix44& _FMat, const Matrix44& _WrdViewMat);
};



////////////////Vertex global operator/////////////////

FORCEINLINE constexpr Vertex operator*(const Vertex& _ref, const float& _ratio)
{
	return std::move(Vertex(_ref.Pos * _ratio, _ref.Color * _ratio, _ref.NormalVec*_ratio, _ref.U * _ratio, _ref.V * _ratio));
}

FORCEINLINE constexpr Vertex operator*(const float& _ratio, const Vertex& _ref)
{
	return std::move(Vertex(_ref.Pos * _ratio, _ref.Color * _ratio, _ref.NormalVec * _ratio, _ref.U * _ratio, _ref.V * _ratio));
}

FORCEINLINE constexpr Vertex operator+(const Vertex& _ref1, const Vertex& _ref2)
{
	return std::move(Vertex(_ref1.Pos + _ref2.Pos, _ref1.Color + _ref2.Color,(_ref1.NormalVec + _ref2.NormalVec).GetNormalVector(), _ref1.U + _ref2.U, _ref1.V + _ref2.V));
}
