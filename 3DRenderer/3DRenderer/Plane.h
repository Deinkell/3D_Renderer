#pragma once
struct Plane
{
public:
	float a, b, c, d;

public:
	Plane() = default;
	FORCEINLINE constexpr Plane(const float& _a, const float& _b, const float& _c, const float& _d)
	: a(_a), b(_b), c(_c), d(_d) {};
	FORCEINLINE constexpr Plane(const float&& _a, const float&& _b, const float&& _c, const float&& _d)
	: a(std::move(_a)), b(std::move(_b)), c(std::move(_c)), d(std::move(_d)) {};
	~Plane() = default;

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

