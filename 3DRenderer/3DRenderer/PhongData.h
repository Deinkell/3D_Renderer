#pragma once
#include "Vector3.h"

struct PhongData
{
public:
	Vector3 Ambient{ 30.0f, 30.0f, 30.0f }, Diffuse{ 255.0f, 100.0f, 100.0f }, Specular{ 255.0f, 255.0f, 255.0f };

public:
	PhongData() = default;
	PhongData(const Vector3& _Amb, const Vector3& _Dif, const Vector3& _Spc)
	: Ambient(_Amb), Diffuse(_Dif), Specular(_Spc)	{};
	~PhongData() = default;

public:
	template<typename T> requires std::is_same_v<T, PhongData>
	FORCEINLINE PhongData operator=(const PhongData& _ref)
	{
		if (&_ref == this)
			return *this;

		Ambient = std::forward<Vector3>(_ref.Ambient);
		Diffuse = std::forward<Vector3>(_ref.Diffuse);
		Specular = std::forward<Vector3>(_ref.Specular);

		return *this;
	}
};

