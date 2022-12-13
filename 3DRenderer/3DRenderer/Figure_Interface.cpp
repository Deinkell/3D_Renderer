#include "stdafx.h"
#include "Figure_Interface.h"

void Figure_Interface::MakeWorldMatrix()
{
	FigureMat44.mat44[0][0] = Scale.X;
	FigureMat44.mat44[1][1] = Scale.Y;
	FigureMat44.mat44[2][2] = Scale.Z;
	FigureMat44.mat44[3][3] = 1.f;

	Matrix44 QuaternionMat;
	MathLib::MakeQuaternionRotateMatrix(&QuaternionMat, Rotation);
	MathLib::CrossProduct(&FigureMat44, QuaternionMat, FigureMat44);

	Matrix44 TransMat;
	TransMat.mat44[3][0] = Position.X;
	TransMat.mat44[3][1] = Position.Z; //Z��� Y�� ��ȯ���� Upvector�� Z���̵ǵ��� �� 
	TransMat.mat44[3][2] = Position.Y; //Z��� Y�� ��ȯ���� Upvector�� Z���̵ǵ��� �� 

	MathLib::CrossProduct(&FigureMat44, TransMat, FigureMat44);
}

void Figure_Interface::MakeViewMatrix()
{

}

void Figure_Interface::MakeProjMatrix()
{

}
