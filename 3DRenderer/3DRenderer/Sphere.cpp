#include "stdafx.h"
#include "Sphere.h"

void Sphere::Init()
{
	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;
	const float N = 0.0f;

	Quaternion tmpVertices[12] =
	{
		Quaternion(-X, N, Z, 1.f), Quaternion(X, N, Z, 1.f), Quaternion(-X, N, -Z, 1.f), Quaternion(X, N, -Z, 1.f),
		Quaternion(N, Z, X, 1.f), Quaternion(N, Z, -X, 1.f), Quaternion(N, -Z, X, 1.f), Quaternion(N, -Z, -X, 1.f),
		Quaternion(Z, X, N, 1.f), Quaternion(-Z, X, N, 1.f), Quaternion(Z, -X, N, 1.f), Quaternion(-Z, -X, N, 1.f)
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
	//20면체 생성
	SubDivide(Sphere_Divide);
	//구로 분할
	for (auto& i : *Vertices)
		i.SetNormalVec();

	Scale.X = 36.f; Scale.Y = 36.f; Scale.Z = 36.f;
}

void Sphere::Move(float _time)
{
}

void Sphere::MakeRenderData()
{
	
	//정점의 래스터라이즈 직전까지 연산작업 
}

void Sphere::Ontick(float _time)
{	
	if(RoateY)
		RotateSun_Y(Vector3(0.f, 0.f, 0.f), _time);
	else
		RotateSun_X(Vector3(0.f, 0.f, 0.f), _time);
}

void Sphere::SubDivide(int _NumOfDivide)
{
	int idxSize, VtxSize;

	for (int i = 0; i < _NumOfDivide; ++i)
	{
		idxSize = Indices->size();
		for (int k = 0; k < idxSize; ++k)
		{
			auto& j = (*Indices)[k];
			VtxSize = Vertices->size();
			Vertex Divide01, Divide02, Divide03;
			Divide01.Pos = ((*Vertices)[j._0].Pos + (*Vertices)[j._1].Pos) * 0.5f;			
			Divide01.Pos = Divide01.Pos.GetNormal();
			Divide01.Pos.W = 1.0f;
			Divide02.Pos = ((*Vertices)[j._0].Pos + (*Vertices)[j._2].Pos) * 0.5f;			
			Divide02.Pos = Divide02.Pos.GetNormal();
			Divide02.Pos.W = 1.0f;
			Divide03.Pos = ((*Vertices)[j._1].Pos + (*Vertices)[j._2].Pos) * 0.5f;			
			Divide03.Pos = Divide03.Pos.GetNormal();
			Divide03.Pos.W = 1.0f;

			Vertices->push_back(Divide01);
			Vertices->push_back(Divide02);
			Vertices->push_back(Divide03);

			Index Dividx01, Dividx02, Dividx03;
			Dividx01._0 = j._0;		Dividx01._1 = VtxSize;     Dividx01._2 = VtxSize + 1;
			Dividx02._0 = j._1;		Dividx02._1 = VtxSize;	   Dividx02._2 = VtxSize + 2;
			Dividx03._0 = j._2;		Dividx03._1 = VtxSize + 1; Dividx03._2 = VtxSize + 2;
			j._0 = VtxSize; j._1 = VtxSize + 1; j._2 = VtxSize + 2;

			Indices->push_back(Dividx01);
			Indices->push_back(Dividx02);
			Indices->push_back(Dividx03);
		}
	}
}

void Sphere::SetNormal(Vertex& _p1, Vertex& _p2, Vertex& _p3)
{
	Vector3 p1p2 = Vector3(_p2.Pos.X, _p2.Pos.Y, _p2.Pos.Z) - Vector3(_p1.Pos.X, _p1.Pos.Y, _p1.Pos.Z);
	Vector3 p1p3 = Vector3(_p3.Pos.X, _p3.Pos.Y, _p3.Pos.Z) - Vector3(_p1.Pos.X, _p1.Pos.Y, _p1.Pos.Z);
	Vector3 Cross = MathLib::CrossProduct(p1p2, p1p3);
	Cross = Cross.GetNormalVector();

	_p1.NormalVec += Cross;
	_p2.NormalVec += Cross;
	_p3.NormalVec += Cross;
}

void Sphere::RotateSun_Y(const Vector3& _Center, const float& _elapsed)
{
	static float theata = 0.f;	
	theata += Rotate_Speed * _elapsed;
	if (theata >= 360.f)
		theata -= 360.f;

	Position.X = Rotate_Dist * sin(theata) + _Center.X;
	Position.Z = Rotate_Dist * cos(theata) + _Center.Z;
}

void Sphere::RotateSun_X(const Vector3& _Center, const float& _elapsed)
{
	static float theata = 0.f;
	theata += Rotate_Speed * _elapsed;
	if (theata >= 360.f)
		theata -= 360.f;

	Position.Y = -Rotate_Dist * sin(theata) + _Center.X;
	Position.Z = -Rotate_Dist * cos(theata) + _Center.Z;
}