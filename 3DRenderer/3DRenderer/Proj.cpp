#include "stdafx.h"
#include "Proj.h"

void Proj::MakeProjMatrix()
{
	float FMinustN = Far - Near;

	if (FMinustN <= 0 || Width <= 0 || Height <= 0)
		return;
	
	ProjMat.mat44[0][0] = 2 * Near / Width;
	ProjMat.mat44[1][1] = 2 * Near / Height;
	ProjMat.mat44[2][2] = Far / FMinustN;
	ProjMat.mat44[2][3] = 1.f;
	ProjMat.mat44[3][2] = -(Far * Near/ FMinustN);
	ProjMat.mat44[3][3] = 0.f;
}
