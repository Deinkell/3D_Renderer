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
	FrustumCulling() = delete; //�⺻ ������ ����, Planes ������ ���ؼ��� ���� �����ϵ�����
	~FrustumCulling() = default;

public:
	BoundCheck CheckBound(const Vector3& _ref);

};

