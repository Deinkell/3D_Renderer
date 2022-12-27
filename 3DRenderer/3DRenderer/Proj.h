#pragma once

struct Matrix44;

class Proj
{
private:
	float Near, Far;
	float Width, Height;
	Matrix44 ProjMat;

public:
	template<typename T> requires std::is_fundamental_v<T>
	FORCEINLINE explicit Proj(T&& _Near, T&& _Far, T&& _Width, T&& _Height_) 
	: Near(_Near), Far(_Far), Width(_Width), Height(_Height_) {};
	Proj() = delete; //기본생성자 삭제, 필요변수들 기입을 통해서만 생성하도록 함
	~Proj() = default;

public:
	FORCEINLINE Matrix44 GetProjMat() { return ProjMat; }

public:
	void MakeProjMatrix();
};

