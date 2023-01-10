#pragma once
#include "Figure_define.h"
#include "Figure_Interface.h"

static constexpr int Sphere_Divide = 3;

class Sphere : public Figure_Interface
{
public:
	FORCEINLINE Sphere() : Figure_Interface(FigureType::Sphere_type) {};
	FORCEINLINE Sphere(const FigureType& _type) : Figure_Interface(_type) {};
	FORCEINLINE Sphere(const Vector3& _pos) : Figure_Interface(_pos, FigureType::Sphere_type) {};
	FORCEINLINE Sphere(const Sphere& _ref) 	: Figure_Interface(_ref) {};
	~Sphere() = default;

public:
	virtual void Init() override;
	virtual void Move(float _time) override;	
	virtual void MakeRenderData() override;
	virtual void Ontick(float _time) override;

public:
	void SubDivide(int _NumOfDivide); //20면체를 쪼개서 구형태로 만들기 위한 작업
	void SetNormal(Vertex& _p1, Vertex& _p2, Vertex& _P3);
	void RotateSun(const Vector3& _Center, const float& _elapsed);
};

