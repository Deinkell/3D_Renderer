#pragma once
#include "Sphere.h"

class LightObj : public Sphere
{
private:
	Vector3 Ambient, Diffuse, Specular;

public:
	static const int ShiningConst = 3;

public:
	LightObj() : Sphere(FigureType::Light_OBJECT) {};
	LightObj(const Vector3& _Amb, const Vector3& _Dif, const Vector3& _Spc) 
	: Ambient(_Amb), Diffuse(_Dif), Specular(_Spc), Sphere(FigureType::Light_OBJECT) {};
	~LightObj() = default;

public:
	FORCEINLINE void SetAmbient(const Vector3& _Amb) { Ambient = _Amb; }
	FORCEINLINE void SetDiffuse(const Vector3& _Dif) { Diffuse = _Dif; }
	FORCEINLINE void SetSpecular(const Vector3& _Spc) { Specular = _Spc; }

};

