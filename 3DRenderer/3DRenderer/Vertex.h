#pragma once

#include "Vector3.h"
#include "Color32.h"
#include "LinearColor.h"

struct Vertex
{
public:
	Quaternion Pos;
	LinearColor Color;
	float U, V;

public:
	Vertex() = default;
	FORCEINLINE Vertex(const Quaternion& _Pos, const LinearColor& _Color, const float _U, const float _V)
	: Pos(_Pos), Color(_Color), U(_U), V(_V){};
	FORCEINLINE Vertex(Quaternion&& _Pos, LinearColor&& _Color, const float&& _U, const float&& _V)
	: Pos(std::move(_Pos)), Color(std::move(_Color)), U(std::move(_U)), V(std::move(_V)) {};
	FORCEINLINE constexpr Vertex(const Vertex& _ref) : Pos(_ref.Pos), Color(_ref.Color), U(_ref.U), V(_ref.V){};
	~Vertex() = default;

public:
	template<typename T> requires std::is_same_v<Vertex, T>
	FORCEINLINE Vertex operator=(T&& _ref) noexcept
	{
		if (this == &_ref)
			return *this;

		Pos = std::forward<Quaternion>((Quaternion)_ref.Pos);
		Color = std::forward<LinearColor>((LinearColor)_ref.Color);
		U = std::forward<float>(_ref.U);
		V = std::forward<float>(_ref.V);

		return *this;
	}
	

public:
	FORCEINLINE Quaternion GetNormalVec() { return std::move(Pos.GetNormal()); }
};


////////////////Vertex global operator/////////////////

FORCEINLINE constexpr Vertex operator*(const Vertex& _ref, const float& _ratio)
{
	return std::move(Vertex(_ref.Pos * _ratio, _ref.Color * _ratio, _ref.U * _ratio, _ref.V * _ratio));
}

FORCEINLINE constexpr Vertex operator*(const float& _ratio, const Vertex& _ref)
{
	return std::move(Vertex(_ref.Pos * _ratio, _ref.Color * _ratio, _ref.U * _ratio, _ref.V * _ratio));
}

FORCEINLINE constexpr Vertex operator+(const Vertex& _ref1, const Vertex& _ref2)
{
	return std::move(Vertex(_ref1.Pos + _ref2.Pos, _ref1.Color + _ref2.Color, _ref1.U + _ref2.U, _ref1.V + _ref2.V));
}
