#pragma once
struct Plane
{
public:
	float a, b, c, d;

public:
	Plane() = default;
	FORCEINLINE Plane(const float& _a, const float& _b, const float& _c, const float& _d)
		: a(_a), b(_b), c(_c), d(_d) {	Normalize(); };
	FORCEINLINE Plane(float&& _a, float&& _b, float&& _c, float&& _d)
	: a(std::move(_a)), b(std::move(_b)), c(std::move(_c)), d(std::move(_d)) {	Normalize(); };
	~Plane() = default;
	
public:
	FORCEINLINE void Normalize();
	FORCEINLINE float GetDistance(const Vector3& _ref) { return MathLib::DotProduct(Vector3(a, b, c), _ref) + d; };
	FORCEINLINE bool IsOutSide(const Vector3& _ref) { return GetDistance(_ref) > 0.f; }

public:
	FORCEINLINE constexpr Plane operator= (const Plane& _Ref)
	{
		if(this == &_Ref)
			return *this;

		a = _Ref.a;
		b = _Ref.b;
		c = _Ref.c;
		d = _Ref.d;	

		return *this;
	}
};

FORCEINLINE void Plane::Normalize()
{
	float SizeSquared = a * a + b * b + c * c;
	SizeSquared = MathLib::GetInvSqrt(SizeSquared);
	a *= SizeSquared;
	b *= SizeSquared;
	c *= SizeSquared;
	d *= SizeSquared;
}
