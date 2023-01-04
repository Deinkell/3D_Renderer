#pragma once
#include "Figure_define.h"
#include "Figure_Interface.h"

class Sphere : public Figure_Interface
{
public:
	FORCEINLINE Sphere() : Figure_Interface(FigureType::Sphere_type) {};
	FORCEINLINE Sphere(const Vector3& _pos) : Figure_Interface(_pos, FigureType::Sphere_type) {};
	FORCEINLINE Sphere(const Sphere& _ref) 	: Figure_Interface(_ref) {};
	~Sphere() = default;

public:
	virtual void Init() override;
	virtual void Move(time_t _time) override;	
	virtual void MakeRenderData() override;
	virtual void Ontick(time_t _time) override;

public:
	void SubDivide(); //20면체를 쪼개서 구형태로 만들기 위한 작업
	void SetNormal(Vertex& _p1, Vertex& _p2, Vertex& _P3);
};

