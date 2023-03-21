#pragma once
#include "Sphere.h"

class LightObj : public Figure_Interface
{
private:
	float KAmbient, KDiffuse, KSpecular;
	float theata;
	float const Rotate_Speed = 45.f;

public:
	static const int ShiningConst = 10;

public:
	LightObj() :KAmbient(0.f), KDiffuse(0.f), KSpecular(0.f), theata(0.f), Figure_Interface(FigureType::Light_OBJECT) {};
	LightObj(const float& _Amb, const float& _Dif, const float& _Spc)
	: KAmbient(_Amb), KDiffuse(_Dif), KSpecular(_Spc), theata(0.f), Figure_Interface(FigureType::Light_OBJECT) {};
	~LightObj() = default;

public:
	FORCEINLINE void SetAmbient(const float& _Amb) { KAmbient = _Amb; }
	FORCEINLINE void SetDiffuse(const float& _Dif) { KDiffuse = _Dif; }
	FORCEINLINE void SetSpecular(const float& _Spc) { KSpecular = _Spc; }
	FORCEINLINE float GetKAmb() { return KAmbient; }
	FORCEINLINE float GetKDiff() { return KDiffuse; }
	FORCEINLINE float GetKSpec() { return KSpecular; }

public:
	virtual void Init() override;
	virtual void Move(float _time) override;
	virtual void MakeRenderData() override;
	virtual void Ontick(float _time) override;
};

