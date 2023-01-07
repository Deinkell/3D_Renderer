#include "stdafx.h"
#include "Vertex.h"


void Vertex::SetNormalVec()
{
	float sqrt = MathLib::GetInvSqrt(Pos.X*Pos.X + Pos.Y*Pos.Y + Pos.Z*Pos.Z);
	NormalVec = std::move(Vector3(Pos.X * sqrt, Pos.Y * sqrt, Pos.Z * sqrt));
}

void Vertex::MakeRenderdata(const Matrix44& _FMat)
{
	Pos = MathLib::CrossProduct(_FMat, Pos);	
	SetNormalVec();
};