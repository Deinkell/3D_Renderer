#include "stdafx.h"
#include "Proj.h"

void Proj::MakeProjMatrix()
{
	if (FMinustN <= 0 || Width <= 0 || Height <= 0)
		return;	
	
	ProjMat.mat44[0][0] = Dist * Width / Height;
	ProjMat.mat44[1][1] = Dist;
	ProjMat.mat44[2][2] = -(Far + Near) / FMinustN;
	ProjMat.mat44[2][3] = -(Near * Far * 2) / FMinustN;
	ProjMat.mat44[3][2] = -1.0f;
	ProjMat.mat44[3][3] = 0.0f;
}
