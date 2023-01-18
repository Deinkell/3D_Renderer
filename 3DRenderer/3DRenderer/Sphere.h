#pragma once
#include "Figure_define.h"
#include "Figure_Interface.h"

static constexpr int Sphere_Divide = 3;
static constexpr float Rotate_Dist = 140.f;
static constexpr float Rotate_Speed = 1.f;

class Sphere : public Figure_Interface
{
private:
	bool RoateY = true;

public:
	FORCEINLINE Sphere() : Figure_Interface(FigureType::Sphere_type) {};
	FORCEINLINE Sphere(const FigureType& _type) : Figure_Interface(_type) {};
	FORCEINLINE Sphere(const Vector3& _pos) : Figure_Interface(_pos, FigureType::Sphere_type) {};
	FORCEINLINE Sphere(const Sphere& _ref) 	: Figure_Interface(_ref) {};
	FORCEINLINE Sphere(const Figure_Interface& _ref) : Figure_Interface(_ref) {};
	~Sphere() = default;

public:
	FORCEINLINE void SetRotateY(bool _b) { RoateY = _b; }

public:
	virtual void Init() override;
	virtual void Move(float _time) override;	
	virtual void MakeRenderData() override;
	virtual void Ontick(float _time) override;

public:
	void SubDivide(int _NumOfDivide); //20면체를 쪼개서 구형태로 만들기 위한 작업
	void SetNormal(Vertex& _p1, Vertex& _p2, Vertex& _P3);
	void RotateSun_Y(const Vector3& _Center, const float& _elapsed);
	void RotateSun_X(const Vector3& _Center, const float& _elapsed);
};

