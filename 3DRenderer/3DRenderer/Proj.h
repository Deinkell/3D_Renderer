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
	Proj() = delete;
	~Proj() = default;

public:
	FORCEINLINE Matrix44 GetProjMat() { return ProjMat; }

public:
	void MakeProjMatrix();
};

