#pragma once

struct LineFunction2D
{
public:
	float Slope = 0.f, Constant = 0.f;
	bool XSlopeZero = false, YSlopeZero = false;
	
public:
	FORCEINLINE bool CheckXYslopeZero() { return XSlopeZero & YSlopeZero; }
};

