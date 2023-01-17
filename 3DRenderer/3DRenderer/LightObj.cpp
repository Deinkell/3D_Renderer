#include "stdafx.h"
#include "LightObj.h"

void LightObj::Init()
{
	float N = 1.f;
	Quaternion tmpVertices[8] =
	{		
		Quaternion(-N, -N, -N, 1.f), Quaternion(N, -N, -N, 1.f),
		Quaternion(N, N, -N, 1.f), 	Quaternion(-N, N, -N, 1.f),
		Quaternion(-N, -N, N, 1.f), Quaternion(N, -N, N, 1.f),
		Quaternion(N, N, N, 1.f),	Quaternion(-N, N, N, 1.f),
	};

	for (int i = 0; i < 8; ++i)
	{
		Vertex tmpVtx;
		tmpVtx.Pos = tmpVertices[i].GetNormal();
		Vertices->push_back(tmpVtx);
	}

	Index tmpIndeces[12] =
	{
		Index(0, 1, 3), Index(3, 1, 2), // Front face.
		Index(0, 1, 4), Index(4, 5, 1), // Bottom face.
		Index(1, 2, 5), Index(5, 6, 2), // Right face.
		Index(2, 3, 6), Index(6, 7, 3), // Top face.
		Index(3, 7, 4), Index(4, 3, 0),	// Left face.
		Index(4, 5, 7), Index(7, 6, 5), // Rear face.
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
	
	theata = Rotate_Speed * _time;
	
	if (Rotation.Y >= 360)
		Rotation.Y -= 360;

	Rotation.Y += theata;	
}
