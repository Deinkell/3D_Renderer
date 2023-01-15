#include "stdafx.h"
#include "LightObj.h"

void LightObj::Init()
{
	Quaternion tmpVertices[8] =
	{
		Quaternion(-0.5f,-0.5f,-0.5f, 1.f), Quaternion(-0.5f, 0.5f,-0.5f, 1.f), 
		Quaternion(0.5f, 0.5f,-0.5f, 1.f), 	Quaternion(0.5f,-0.5f,-0.5f, 1.f),
		Quaternion(-0.5f,-0.5f, 0.5f, 1.f), Quaternion(-0.5f, 0.5f, 0.5f, 1.f), 
		Quaternion(0.5f, 0.5f, 0.5f, 1.f),	Quaternion(0.5f,-0.5f, 0.5f, 1.f),	
	};

	for (int i = 0; i < 8; ++i)
	{
		Vertex tmpVtx;
		tmpVtx.Pos = tmpVertices[i].GetNormal();
		Vertices->push_back(tmpVtx);
	}

	Index tmpIndeces[12] =
	{
		Index(0,1,2), Index(0,2,3), Index(4,6,5), Index(4,7,6), 
		Index(0,4,5), Index(0,5,1), Index(1,5,6), Index(1,6,2),
		Index(2,6,7), Index(2,7,3),	Index(3,7,4), Index(3,4,0),	
	};

	for (int i = 0; i < 12; ++i)
		Indices->push_back(tmpIndeces[i]);	

	for (auto& i : *Vertices)
		i.SetNormalVec();

	Scale.X = 30.f; Scale.Y = 30.f; Scale.Z = 30.f;
}

void LightObj::Move(float _time)
{
}

void LightObj::MakeRenderData()
{
}

void LightObj::Ontick(float _time)
{
	/*
	theata = Rotate_Speed * _time;
	
	if (Rotation.Y >= 360)
		Rotation.Y -= 360;

	Rotation.Y += theata;
	*/
}
