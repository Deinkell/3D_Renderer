#include "stdafx.h"
#include "Render.h"

void Render::OnRender()
{
}

void Render::BackSpaceCuling()
{
}

void Render::PlaneCulling()
{
}

void Render::RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, DibSection& _DibSec)
{
	Vector3 Vertices[3]{ _p1.Pos, _p2.Pos, _p3.Pos };
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
				MathLib::SwapElement(StartX, EndX);
			
			for (int j = StartX; j < EndX; j++)
			{
				//PlaneCliping 위치
				//Zbuffer 그리기 확인위치
				//PhongShader(폴리곤 노말값을 통한 램버트 반사값 계산위치)
		
				_DibSec.DotPixel(j, i, _p1.Color);
			}
		}
		else//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 클 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
					EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);

			if (StartX < EndX)
				MathLib::SwapElement(StartX, EndX);

			for (int j = StartX; j < EndX; j++)
			{
				//PlaneCliping 위치
				//Zbuffer 그리기 확인위치
				//PhongShader(폴리곤 노말값을 통한 램버트 반사값 계산위치)

				_DibSec.DotPixel(j, i, _p1.Color);
			}
		}
	}
}
