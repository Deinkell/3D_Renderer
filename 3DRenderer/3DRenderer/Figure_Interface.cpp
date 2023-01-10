#include "stdafx.h"
#include "Figure_Interface.h"

void Figure_Interface::MakeWorldMatrix(Matrix44* _Out)
{
	MathLib::InitUnitMatrix44(_Out);
	_Out->mat44[0][0] = Scale.X;
	_Out->mat44[1][1] = Scale.Y;
	_Out->mat44[2][2] = Scale.Z;
	_Out->mat44[3][3] = 1.f;
	
	Matrix44 QuaternionMat;
	MathLib::MakeQuaternionRotateMatrix(&QuaternionMat, Rotation);
	MathLib::CrossProduct(_Out, *_Out, QuaternionMat);
	
	Matrix44 TransMat;
	TransMat.mat44[3][0] = Position.X;
	TransMat.mat44[3][1] = Position.Y; //Z축과 Y축 교환으로 Upvector가 Z축이되도록 함(입력값의 수정, 계산식은 동일) 
	TransMat.mat44[3][2] = Position.Z; //Z축과 Y축 교환으로 Upvector가 Z축이되도록 함(입력값의 수정, 계산식은 동일) 

	MathLib::CrossProduct(_Out, *_Out, TransMat);
}

void Figure_Interface::MakeViewMatrix(Matrix44* _Out, const Matrix44& _CameraMatrix)
{
	MathLib::CrossProduct(_Out, *_Out, _CameraMatrix);
}

void Figure_Interface::MakeProjMatrix(Matrix44* _Out, const Matrix44& _ProjMat)
{
	MathLib::CrossProduct(_Out, *_Out, _ProjMat);
}
