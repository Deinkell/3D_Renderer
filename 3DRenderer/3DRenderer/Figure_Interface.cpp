#include "stdafx.h"
#include "Figure_Interface.h"

void Figure_Interface::MakeWorldMatrix(Matrix44* _Out)
{
	
	Matrix44 Result;
	MathLib::InitUnitMatrix44(_Out);
	Result.mat44[0][0] = Scale.X;
	Result.mat44[1][1] = Scale.Y;
	Result.mat44[2][2] = Scale.Z;
	Result.mat44[3][3] = 1.f;
	
	Matrix44 QuaternionMat;
	MathLib::MakeQuaternionRotateMatrix(&QuaternionMat, Rotation);
	MathLib::CrossProduct(&Result, Result, QuaternionMat);		
	//쿼터니온 회전연산식
	/*
	Matrix44 MatX, MatY, MatZ;
	MatXspin(&MatX, Rotation.X);
	MathLib::CrossProduct(&Result, Result, MatX);

	MatYspin(&MatY, Rotation.Y);
	MathLib::CrossProduct(&Result, Result, MatY);

	MatZspin(&MatZ, Rotation.Z);
	MathLib::CrossProduct(&Result, Result, MatZ);
	*///회전행렬 연산식

	Matrix44 TransMat;
	TransMat.mat44[3][0] = Position.X;
	TransMat.mat44[3][1] = Position.Y; //Z축과 Y축 교환으로 Upvector가 Z축이되도록 함(입력값의 수정, 계산식은 동일) 
	TransMat.mat44[3][2] = Position.Z; //Z축과 Y축 교환으로 Upvector가 Z축이되도록 함(입력값의 수정, 계산식은 동일) 
	MathLib::CrossProduct(&Result, Result, TransMat);	
	
	*_Out = Result;
}
Figure_Interface::~Figure_Interface()
{

}

void Figure_Interface::MakeWorldMatrix_Inv(Matrix44* _Out)
{
	Matrix44 Result;
	MathLib::InitUnitMatrix44(_Out);
	Result.mat44[0][0] = Scale.X;
	Result.mat44[1][1] = Scale.Y;
	Result.mat44[2][2] = Scale.Z;
	Result.mat44[3][3] = 1.f;

	Matrix44 QuaternionMat;
	MathLib::MakeQuaternionRotateMatrix_Inv(&QuaternionMat, Rotation);
	MathLib::CrossProduct(&Result, Result, QuaternionMat);
	//쿼터니온 회전연산식
	/*
	Matrix44 MatX, MatY, MatZ;
	MatXspin(&MatX, Rotation.X);
	MathLib::CrossProduct(&Result, Result, MatX);

	MatYspin(&MatY, Rotation.Y);
	MathLib::CrossProduct(&Result, Result, MatY);

	MatZspin(&MatZ, Rotation.Z);
	MathLib::CrossProduct(&Result, Result, MatZ);
	*///회전행렬 연산식
		
	Result.mat44[0][3] = Position.X;
	Result.mat44[1][3] = Position.Y; //Z축과 Y축 교환으로 Upvector가 Z축이되도록 함(입력값의 수정, 계산식은 동일) 
	Result.mat44[2][3] = Position.Z; //Z축과 Y축 교환으로 Upvector가 Z축이되도록 함(입력값의 수정, 계산식은 동일) 

	*_Out = Result;
}

void Figure_Interface::MatXspin(Matrix44* _Out, const float& _Xspin)
{
	_Out->mat44[0][0] = 1;
	_Out->mat44[1][1] = (float)cos((double)((_Xspin * 3.14) / 180));
	_Out->mat44[1][2] = (float)-sin((double)((_Xspin * 3.14) / 180));
	_Out->mat44[2][1] = (float)sin((double)((_Xspin * 3.14) / 180));
	_Out->mat44[2][2] = (float)cos((double)((_Xspin * 3.14) / 180));
	_Out->mat44[3][3] = 1;
}

void Figure_Interface::MatYspin(Matrix44* _Out, const float& _Yspin)
{
	_Out->mat44[0][0] = (float)cos((double)((_Yspin * 3.14) / 180));
	_Out->mat44[0][2] = (float)-sin((double)((_Yspin * 3.14) / 180));
	_Out->mat44[1][1] = 1;
	_Out->mat44[2][0] = (float)sin((double)((_Yspin * 3.14) / 180));
	_Out->mat44[2][2] = (float)cos((double)((_Yspin * 3.14) / 180));
	_Out->mat44[3][3] = 1;
}

void Figure_Interface::MatZspin(Matrix44* _Out, const float& _Zspin)
{
	_Out->mat44[0][0] = (float)cos((double)((_Zspin * 3.14) / 180));
	_Out->mat44[0][1] = (float)-sin((double)((_Zspin * 3.14) / 180));
	_Out->mat44[1][0] = (float)sin((double)((_Zspin * 3.14) / 180));
	_Out->mat44[1][1] = (float)cos((double)((_Zspin * 3.14) / 180));
	_Out->mat44[2][2] = 1;
	_Out->mat44[3][3] = 1;
}

void Figure_Interface::MakeViewMatrix(Matrix44* _Out, const Matrix44& _CameraMatrix)
{
	MathLib::CrossProduct(_Out, WorldMat, _CameraMatrix);	
}

void Figure_Interface::MakeViewMatrix_Inv(Matrix44* _Out, const Matrix44& _CameraMatrix)
{
	MathLib::CrossProduct(_Out, _CameraMatrix, WorldMat);
}

void Figure_Interface::MakeProjMatrix(Matrix44* _Out, const Matrix44& _ProjMat)
{
	MathLib::CrossProduct(_Out, *_Out, _ProjMat);	
}

void Figure_Interface::MakeProjMatrix_Inv(Matrix44* _Out, const Matrix44& _ProjMat)
{
	MathLib::CrossProduct(_Out, _ProjMat, *_Out);
}
