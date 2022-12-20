#include "stdafx.h"
#include "Camera.h"

void Camera::Initialize()
{
	Vector3 tempUpVector{ 0.f, 1.f, 0.f }; //ฟ๙ตๅ พ๗บคลอ
	Direction[2] = LookAt - Position; //Front
	Direction[1] = MathLib::CrossProduct(Direction[2], tempUpVector); //Right
	Direction[0] = MathLib::CrossProduct(Direction[1], Direction[2]); //Up
};

void Camera::MakeViewMatrix()
{
	CameraMat.mat44[0][0] = Direction[1].X; //Right บคลอ
	CameraMat.mat44[1][0] = Direction[1].Y;
	CameraMat.mat44[2][0] = Direction[1].Z;
	CameraMat.mat44[3][0] = 0.f;

	CameraMat.mat44[0][1] = Direction[0].X; //UP บคลอ
	CameraMat.mat44[1][1] = Direction[0].Y;
	CameraMat.mat44[2][1] = Direction[0].Z;
	CameraMat.mat44[3][1] = 0.f;

	CameraMat.mat44[0][2] = Direction[2].X; //Front บคลอ
	CameraMat.mat44[1][2] = Direction[2].Y;
	CameraMat.mat44[2][2] = Direction[2].Z;
	CameraMat.mat44[3][2] = 0.f;

	CameraMat.mat44[3][0] = -(Position.X * Direction[1].X + Position.Y * Direction[1].Y + Position.Z * Direction[1].Z);
	CameraMat.mat44[3][1] = -(Position.X * Direction[0].X + Position.Y * Direction[0].Y + Position.Z * Direction[0].Z);
	CameraMat.mat44[3][2] = -(Position.X * Direction[2].X + Position.Y * Direction[2].Y + Position.Z * Direction[2].Z);
	CameraMat.mat44[3][3] = 1.f;
};
