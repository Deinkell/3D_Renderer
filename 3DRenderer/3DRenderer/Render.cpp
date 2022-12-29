#include "stdafx.h"
#include "Render.h"

Render::Render()
{
	DibSec.InitializeDib();
}

void Render::OnRender()
{
	if (ThreadPool_Component == nullptr || ObjectMng_Component == nullptr)
		return;


}

void Render::BackSpaceCuling()
{
}

void Render::PlaneCulling()
{
}

void Render::RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, DibSection& _DibSec)
{
	std::vector<Vertex> tmpVertices{ _p1, _p2, _p3 };
	std::vector<PerspectiveTest> testPlanes = {
		{TestFuncW0, EdgeFuncW0},
		{TestFuncNY, EdgeFuncNY},
		{TestFuncPY, EdgeFuncPY},
		{TestFuncNX, EdgeFuncNX},
		{TestFuncPX, EdgeFuncPX},
		{TestFuncFar, EdgeFuncFar},
		{TestFuncNear, EdgeFuncNear}
	};

	for (auto& p : testPlanes)
		p.ClipTriangles(tmpVertices); //삼각형 클리핑(ndc 공간에서 삼각형 보정진행)

	if (tmpVertices.size() == 0)
		return;

	Vector3 Vertices[3]{ Vector3(tmpVertices[0].Pos.X, tmpVertices[0].Pos.Y, tmpVertices[0].Pos.Z),
						Vector3(tmpVertices[1].Pos.X, tmpVertices[1].Pos.Y, tmpVertices[1].Pos.Z),
						Vector3(tmpVertices[2].Pos.X, tmpVertices[2].Pos.Y, tmpVertices[2].Pos.Z)};
	MathLib::SortByYvalue(Vertices, Vertices);
	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);

	for (int i = Vertices[2].Y; i <= Vertices[0].Y; i++)
	{
		if (i <= Vertices[1].Y)//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 작을 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i), 
					EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);

			if (StartX < EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
			//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
			//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)
			for (int j = StartX; j <= EndX; j++)
			{
				//Zbuffer 그리기 확인위치
				//PhongShader(폴리곤 노말값을 통한 램버트 반사값 계산위치)
		
				_DibSec.DotPixel(j, i, _p1.Color.ToColor32());
			}
		}
		else//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 클 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
					EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);

			if (StartX < EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
			//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
			//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)
			for (int j = StartX; j <= EndX; j++)
			{
				//Zbuffer 그리기 확인위치
				//PhongShader(폴리곤 노말값을 통한 램버트 반사값 계산위치)

				_DibSec.DotPixel(j, i, _p1.Color.ToColor32());
			}
		}
	}
}
