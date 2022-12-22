#pragma once

struct Matrix44;

class Proj
{
private:
	Matrix44 ProjMat;

public:
	Proj() = default;
	~Proj() = default;

public:
	void MakeProjMatrix();
};

