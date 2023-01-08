#include "stdafx.h"
#include "Vertex.h"


void Vertex::SetNormalVec()
{
	float invsqrt = MathLib::GetInvSqrt(Pos.X*Pos.X + Pos.Y*Pos.Y + Pos.Z*Pos.Z);
	NormalVec = std::move(Vector3(Pos.X * invsqrt, Pos.Y * invsqrt, Pos.Z * invsqrt));
}

void Vertex::MakeRenderdata(const Matrix44& _FMat)
{
	Pos = MathLib::CrossProduct(_FMat, Pos);	
	SetNormalVec();
};