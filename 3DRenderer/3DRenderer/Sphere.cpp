#include "stdafx.h"
#include "Sphere.h"

void Sphere::Init()
{
	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;
	const float N = 0.0f;

	Vector3 tmpVertices[12] =
	{
		Vector3(-X, N, Z), Vector3(X, N, Z), Vector3(-X, N, -Z), Vector3(X, N, -Z),
		Vector3(N, Z, X), Vector3(N, Z, -X), Vector3(N, -Z, X), Vector3(N, -Z, -X),
		Vector3(Z, X, N), Vector3(-Z, X, N), Vector3(Z, -X, N), Vector3(-Z, -X, N)
	};

	for (int i = 0; i < 12; ++i)
	{
		Vertex tmpVtx;
		tmpVtx.Pos = tmpVertices[i];
		Vertices->push_back(tmpVtx);
	}

	Index tmpIndeces[20] =
	{
		Index(0, 4, 1), Index(0, 9, 4), Index(9, 5, 4), Index(4, 5, 8), Index(4, 8, 1),
		Index(8, 10, 1), Index(8, 3, 10), Index(5, 3, 8), Index(5, 2, 3), Index(2, 7, 3),
		Index(7, 10, 3), Index(7, 6, 10), Index(7, 11, 6), Index(11, 0, 6), Index(0, 1, 6),
		Index(6, 1, 10), Index(9, 0, 11), Index(9, 11, 2), Index(9, 2, 5), Index(7, 2, 11)
	};

	for (int i = 0; i < 20; ++i)
		Indices->push_back(tmpIndeces[i]);
}

void Sphere::Move(time_t _time)
{
}

void Sphere::MakeRenderData()
{
}

void Sphere::Ontick()
{
}

void Sphere::SubDivide()
{
}
