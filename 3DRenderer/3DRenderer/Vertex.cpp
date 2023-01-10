#include "stdafx.h"
#include "Vertex.h"


void Vertex::SetNormalVec()
{
	float invsqrt = MathLib::GetInvSqrt(Pos.X*Pos.X + Pos.Y*Pos.Y + Pos.Z*Pos.Z);
	NormalVec = std::move(Vector3(Pos.X * invsqrt, Pos.Y * invsqrt, Pos.Z * invsqrt));
}

void Vertex::MakeRenderdata(const Matrix44& _FMat, const Matrix44& _WrdViewMat)
{
	Pos = MathLib::CrossProduct(_FMat, Pos);	
	Quaternion tmp(NormalVec.X, NormalVec.Y, NormalVec.Z, 0.f);
	MathLib::CrossProduct(_WrdViewMat, tmp);
	NormalVec = Vector3(tmp.X, tmp.Y, tmp.Z).GetNormalVector();
};