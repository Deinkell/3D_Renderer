#include "stdafx.h"
#include "Render.h"

Render::Render()
{
	DibSec.InitializeDib();
	DepthBuf.Initialize(DibSec.GetClientX(), DibSec.GetClientY());
	InitializeCriticalSection(&CRSC);
}

Render::~Render()
{
	DeleteCriticalSection(&CRSC);
}

void Render::Initialize(std::shared_ptr<ObjectMNG>& _ObjMng, std::shared_ptr<ThreadPool>& _Thdpool, std::shared_ptr<Camera>& _Camera)
{
	ObjectMng_Component = _ObjMng;
	ThreadPool_Component = _Thdpool;
	Camera_Component = _Camera;
}

void Render::OnRender(float _elapsedTime)
{
	if (ThreadPool_Component == nullptr || ObjectMng_Component == nullptr)
		return;

	Vertex tmp[3];
	tmp[0].Pos = Quaternion(10.f, 10.f, 0.1f, 1.f); tmp[0].Color.G = 1.f;
	tmp[1].Pos = Quaternion(20.f, 30.f, 0.1f, 1.f);
	tmp[2].Pos = Quaternion(40.f, 20.f, 0.1f, 1.f);

	Vertex tmp1[3];
	tmp1[0].Pos = Quaternion(30.f, 10.f, 0.1f, 1.f); tmp1[0].Color.B = 1.f;
	tmp1[1].Pos = Quaternion(40.f, 30.f, 0.1f, 1.f);
	tmp1[2].Pos = Quaternion(60.f, 20.f, 0.1f, 1.f);

	ThreadPool_Component->EnqueueJob([this](Vertex tmp[]) { RasterizePolygon(tmp[0], tmp[1], tmp[2]); }, tmp);
	ThreadPool_Component->EnqueueJob([this](Vertex tmp[]) { RasterizePolygon(tmp[0], tmp[1], tmp[2]); }, tmp1);

	DibSec.BitBltDibSection();
	DepthBuf.ClearDepthBuffer();
}

void Render::BackSpaceCuling()
{
}

Vector3 Render::Geometric_centroid_VertexCalc(const Vector3& _p3p1Vec, const Vector3& _p3p2Vec, const Vector3& _W)
{
	Vector3 u = _p3p1Vec, v = _p3p2Vec;
	float udotv = MathLib::DotProduct(u.X, u.Y, v.X, v.Y),
		  wdotv = MathLib::DotProduct(_W.X, _W.Y, v.X, v.Y),
		  wdotu = MathLib::DotProduct(_W.X, _W.Y, u.X, u.Y),
		  uu = MathLib::DotProduct(u.X, u.Y, u.X, u.Y),
		  vv = MathLib::DotProduct(v.X, v.Y, v.X, v.Y);

	float t = (wdotu * udotv - wdotv * uu) / ((udotv * udotv) - uu * vv);
	float s = (wdotv*udotv - wdotu*vv) / (udotv*udotv - uu*vv);
	return std::move(Vector3(s, t, 1 - s - t));
}

void Render::RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3)
{
	/*
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
	*/
/**************임시****************/
	Vector3 Vertices[3]{ Vector3(_p1.Pos.X, _p1.Pos.Y, _p1.Pos.Z),
						Vector3(_p2.Pos.X, _p2.Pos.Y, _p2.Pos.Z),
						Vector3(_p3.Pos.X, _p3.Pos.Y, _p3.Pos.Z) };
/**************임시****************/
	int CorrectionX = DibSec.GetClientX() / 2, CorrectionY = DibSec.GetClientY() / 2;
	int ResultX, ResultY;

	MathLib::SortByYvalue(Vertices, Vertices);
	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);

	for (int i = Vertices[0].Y; i <= Vertices[2].Y; i++)
	{
		if (i <= Vertices[1].Y)//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 작을 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i), 
					EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);

			if (StartX > EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
			//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
			//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)
			for (int j = StartX; j <= EndX; j++)
			{
				ResultX = j + CorrectionX; 
				ResultY = i + CorrectionY;				
				//PhongShader(폴리곤 노말값을 통한 램버트 반사값 계산위치)
				if(!DibSec.CheckIntersectClientRect(ResultX, ResultY))
					continue;

				Vector3 GeoPos = Geometric_centroid_VertexCalc(Vertices[0] - Vertices[2], 
													Vertices[1] - Vertices[2], Vector3(ResultX, ResultY, 0));

				float PixelZvalue = Vertices[0].Z * GeoPos.X + Vertices[1].Z * GeoPos.Y + Vertices[2].Z * GeoPos.Z;
				
			
				EnterCriticalSection(&CRSC);
				if (!DepthBuf.CheckDepthBuffer(ResultX, ResultY, PixelZvalue))
				{
					LeaveCriticalSection(&CRSC);
					continue;
				}
				LeaveCriticalSection(&CRSC);
				//깊이버퍼 체크			
				
				DibSec.DotPixel(ResultX, ResultY, _p1.Color.ToColor32());		
			}
		}
		else//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 클 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
					EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);

			if (StartX > EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
			//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
			//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)
			for (int j = StartX; j <= EndX; j++)
			{
				ResultX = j + CorrectionX;
				ResultY = i + CorrectionY;				
				//PhongShader(폴리곤 노말값을 통한 램버트 반사값 계산위치)
				if (!DibSec.CheckIntersectClientRect(ResultX, ResultY))
					continue;

				Vector3 GeoPos = Geometric_centroid_VertexCalc(Vertices[0] - Vertices[2],
												Vertices[1] - Vertices[2], Vector3(ResultX, ResultY, 0));

				float PixelZvalue = Vertices[0].Z * GeoPos.X + Vertices[1].Z * GeoPos.Y + Vertices[2].Z * GeoPos.Z;

				EnterCriticalSection(&CRSC);
				if (!DepthBuf.CheckDepthBuffer(ResultX, ResultY, PixelZvalue))
				{
					LeaveCriticalSection(&CRSC);
					continue;					
				}
				LeaveCriticalSection(&CRSC);
				//깊이버퍼 체크			
				
				DibSec.DotPixel(ResultX, ResultY, _p1.Color.ToColor32());				
			}
		}
	}
}

Color32 Render::MakePhongShader(const Vector3& _ObjPos, const Vector3& _PixelNormal)
{
	//방향광을 전제로 계산(픽셀에서 광원과의 노말을 구하는데는 연산량이 너무 늘어나서 방향광으로 선택)
	LightObj* Lighting = ObjectMng_Component->GetLightSun();
	Vector3 l_DirLight = _ObjPos - Lighting->GetPosition();
	Vector3 v_ObjToCamera = _ObjPos - Camera_Component->GetPosition();
	Vector3 r_ReflectVec = -1 * 2 * (MathLib::DotProduct((-1 * l_DirLight), _PixelNormal)) * _PixelNormal - l_DirLight;
	float a_Shining = LightObj::ShiningConst;

	//믈체별로 Material(Ambient, Diffuse, Specular)값을 필요로하는듯, 확인 후 추가 필요

	return Color32();
}

void Render::RenderFPS(float _elapsedTime)
{
	DibSec.SetWindowsTitleFPS(_elapsedTime);
}
