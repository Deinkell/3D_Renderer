#pragma once
#include "Figure_Interface.h"

class Sphere : public Figure_Interface
{
public:
	Sphere() = default;
	FORCEINLINE Sphere(const Sphere& _ref)
	: Figure_Interface(_ref) {};
	~Sphere() = default;

public:
	virtual void Init() override;
	virtual void Move(time_t _time) override;	
	virtual void MakeRenderData() override;
	virtual void Ontick() override;

public:
	void SubDivide(); //20면체를 쪼개서 구형태로 만들기 위한 작업
};

