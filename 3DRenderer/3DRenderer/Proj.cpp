#include "stdafx.h"
#include "Proj.h"

void Proj::MakeProjMatrix()
{
	if (Width <= 0 || Height <= 0)
		return;	
	//Aspect
	ProjMat.mat44[0][0] = Dist / Aspect;
	ProjMat.mat44[1][1] = Dist;
	ProjMat.mat44[2][2] = (Far + Near) / NMinustF;
	ProjMat.mat44[2][3] = (2 *Far * Near) / NMinustF;
	ProjMat.mat44[3][2] = 1.f;
	ProjMat.mat44[3][3] = 0.f;	
}

void Proj::MakeProjMatrix_Inv()
{
	if (Width <= 0 || Height <= 0)
		return;
	//Aspect
	ProjMat.mat44[0][0] = Dist / Aspect;
	ProjMat.mat44[1][1] = Dist;
	ProjMat.mat44[2][2] = (Far + Near) / NMinustF;
	ProjMat.mat44[2][3] = -1.f;
	ProjMat.mat44[3][2] = (2 * Far * Near) / NMinustF;;
	ProjMat.mat44[3][3] = 0.f;
}
