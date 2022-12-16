#pragma once

#include "Vector3.h"
#include "Color32.h"

struct Vertex
{
public:
	Vector3 Pos;
	Color32 Color;	

public:
	Vertex() = default;
	FORCEINLINE Vertex(const Vector3& _Pos, const Color32& _Color)
	: Pos(_Pos), Color(_Color){};
	FORCEINLINE Vertex(Vector3&& _Pos, Color32&& _Color, bool&& _CalcPixcel)
	: Pos(std::move(_Pos)), Color(std::move(_Color)) {};
	~Vertex() = default;

public:
	template<typename T> requires std::is_same_v<Vertex, T>
	FORCEINLINE Vertex operator=(T&& _ref)
	{
		if (this == &_ref)
			return *this;

		Pos = std::forward<Vector3>(_ref.Pos);
		Color = std::forward<Color32>(_ref.Color);

		return *this;
	}

public:
	FORCEINLINE Vector3 GetNormalVec() { return std::move(Pos.GetNormalVector()); }
	FORCEINLINE UINT32 GetColorValue() { return std::move(Color.GetColorRef()); }
};

