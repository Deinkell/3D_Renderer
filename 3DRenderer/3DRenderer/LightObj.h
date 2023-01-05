#pragma once
#include "Sphere.h"

class LightObj : public Sphere
{
private:
	float KAmbient, KDiffuse, KSpecular;

public:
	static const int ShiningConst = 3;

public:
	LightObj() : Sphere(FigureType::Light_OBJECT) {};
	LightObj(const float& _Amb, const float& _Dif, const float& _Spc)
	: KAmbient(_Amb), KDiffuse(_Dif), KSpecular(_Spc), Sphere(FigureType::Light_OBJECT) {};
	~LightObj() = default;

public:
	FORCEINLINE void SetAmbient(const float& _Amb) { KAmbient = _Amb; }
	FORCEINLINE void SetDiffuse(const float& _Dif) { KDiffuse = _Dif; }
	FORCEINLINE void SetSpecular(const float& _Spc) { KSpecular = _Spc; }
	FORCEINLINE float GetKAmb() { return KAmbient; }
	FORCEINLINE float GetKDiff() { return KDiffuse; }
	FORCEINLINE float GetKSpec() { return KSpecular; }
};

