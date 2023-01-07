#include "stdafx.h"
#include "Vertex.h"


void Vertex::MakeRenderdata(const Matrix44& _FMat)
{
	Pos = MathLib::CrossProduct(_FMat, Pos);
	NormalVec = NormalVec.GetNormalVector();
};