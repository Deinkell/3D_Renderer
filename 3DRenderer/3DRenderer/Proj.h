#pragma once

#define PROJECTION_FOV 60.f

struct Matrix44;

class Proj
{
private:
	float Near, Far;
	float Width, Height, FMinustN, Fovy, Dist;
	Matrix44 ProjMat;

public:
	template<typename T> requires std::is_fundamental_v<T>
	FORCEINLINE explicit Proj(T&& _Near, T&& _Far, T&& _Width, T&& _Height_) 
	: Near(_Near), Far(_Far), Width(_Width), Height(_Height_) 
	{
		FMinustN = Far - Near;
		Fovy = (float)(PROJECTION_FOV * 3.14 / 180.0f);
		Dist = 1.0f / tanf(Fovy / 2.0f);
	};
	Proj() = delete; //�⺻������ ����, �ʿ亯���� ������ ���ؼ��� �����ϵ��� ��
	~Proj() = default;

public:
	FORCEINLINE Matrix44 GetProjMat() { return ProjMat; }

public:
	void MakeProjMatrix();
};

