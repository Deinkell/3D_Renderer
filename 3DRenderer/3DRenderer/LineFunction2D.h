#pragma once
#include "Vector3.h"

struct LineFunction2D
{
public:
	float Slope = 0.f, Constant = 0.f;
	bool XSlopeZero = false, YSlopeZero = false;
	
public:
	FORCEINLINE constexpr float GetXValueByPoint(const float& _X, const float& _Y);
	FORCEINLINE constexpr float GetYValueByPoint(const float& _X, const float& _Y);
};

FORCEINLINE constexpr float LineFunction2D::GetXValueByPoint(const float& _X, const float& _Y)
{
	if(XSlopeZero)
		return _Y;

	if(YSlopeZero)
		return _X;

	return std::move((_Y - Constant) / Slope);
};

FORCEINLINE constexpr float LineFunction2D::GetYValueByPoint(const float& _X, const float& _Y)
{
	if (XSlopeZero)
		return _Y;

	if (YSlopeZero)
		return _X;

	return std::move((Slope * _X)  + Constant);
};