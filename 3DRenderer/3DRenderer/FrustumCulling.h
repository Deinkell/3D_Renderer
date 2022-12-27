#pragma once

struct Matrix44;

enum class BoundCheck : char
{
	Outside,
	Intersect,
	Inside
};

class FrustumCulling
{
private:
	std::span<Plane> Planes;

public:
	FORCEINLINE explicit FrustumCulling(std::span<Plane> _Planes) : Planes(_Planes) {};
	FrustumCulling() = delete; //기본 생성자 삭제, Planes 대입을 통해서만 생성 가능하도록함
	~FrustumCulling() = default;

public:
	BoundCheck CheckBound(const Vector3& _ref);

};

