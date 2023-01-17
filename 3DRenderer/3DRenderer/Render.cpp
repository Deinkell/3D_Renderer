#include "stdafx.h"
#include "Render.h"

Render::Render(HWND _hWnd)
{
	DibSec.InitializeDib(_hWnd);
	DepthBuf.Initialize(DibSec.GetClientX(), DibSec.GetClientY());	
	InitializeCriticalSection(&CRSC);
	Projection = std::make_unique<Proj>(1, 1000, DibSec.GetClientX(), DibSec.GetClientY());
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

	ClientX = DibSec.GetClientX() / 2;
	ClientY = DibSec.GetClientY() / 2;

	MakeViewPortMat();
}

void Render::MakeViewPortMat()
{	

	ViewPortMat.mat44[0][0] = ClientX;
	ViewPortMat.mat44[1][1] = -ClientY;
	ViewPortMat.mat44[2][2] = 1;

	ViewPortMat.mat44[3][0] = ClientX;
	ViewPortMat.mat44[3][1] = ClientY;
	ViewPortMat.mat44[3][2] = 0.f;
}

void Render::OnRender(float _elapsedTime)
{
	if (ThreadPool_Component == nullptr || ObjectMng_Component == nullptr || Camera_Component == nullptr)
		return;

	PrepareObj_for_Render();
	RenderObj();
	BitBltDib();		
}

void Render::PrepareObj_for_Render()
{
	Camera_Component->MakeViewMatrix_Inv();
	ObjectMng_Component->PrepareRender_MakeMat(Camera_Component->GetCameraMat(), Projection->GetProjMat());
}

void Render::MakePolygonNDCData(Vertex* _Polygon)
{
	for (int i = 0; i < 3; i++)
	{
		_Polygon[i].Pos.X = _Polygon[i].Pos.X / _Polygon[i].Pos.W;
		_Polygon[i].Pos.Y = _Polygon[i].Pos.Y / _Polygon[i].Pos.W;
		_Polygon[i].Pos.Z = _Polygon[i].Pos.Z / _Polygon[i].Pos.W;	
	}
}

void Render::MakePolygonViewPortData(std::vector<Vertex>& _vt)
{
	for (auto& i : _vt)
	{	
		//i.Pos = MathLib::CrossProduct(ViewPortMat, i.Pos); //뷰포트 행렬 곱 연산
		i.Pos.X = i.Pos.X * ClientX + ClientX;
		i.Pos.Y = -i.Pos.Y * ClientY + ClientY;	
	}
}

void Render::RenderObj()
{
	int ObjSize = ObjectMng_Component->GetObjectVectorSize();
	for (int i = 0; i < ObjSize; i++)
	{
		std::shared_ptr<std::vector<Vertex>> Vertices = ObjectMng_Component->GetObj_Vertices(i);
		std::shared_ptr<std::vector<Index>> Indicies = ObjectMng_Component->GetObj_Indicies(i);
		Vector3 Position = ObjectMng_Component->GetObj_Position(i);
		PhongData PhoD = ObjectMng_Component->GetPhongData(i);
		Matrix44 FMat = ObjectMng_Component->GetObj_FinalMatrix(i);
		Matrix44 WrdMat = ObjectMng_Component->GetObj_WrdMat(i);	
		Matrix44 WrdviewMat = ObjectMng_Component->GetObj_WrdViewMat(i);
		Render_Type = ObjectMng_Component->GetRenderType(i);
		//Render_Type = RenderType::WireFrame;
		//Render_Type = RenderType::basic;
		Thread_Render = true;		

		for (auto& j : *Indicies)
		{		
			Vertex tmp[3]{ (*Vertices)[j._0] , (*Vertices)[j._1] , (*Vertices)[j._2] };		

			tmp[0].MakeRenderdata_Inv(FMat, WrdMat);
			tmp[1].MakeRenderdata_Inv(FMat, WrdMat);
			tmp[2].MakeRenderdata_Inv(FMat, WrdMat);
			MakePolygonNDCData(tmp);//동차좌표계로 변환
			SwithRenderType(Position, tmp[0], tmp[1], tmp[2], PhoD);
		}		
	}
}

bool Render::BackFaceCuling(const Vector3& _Normal)
{
	if (0.f <= MathLib::DotProduct(Camera_Component->GetNormal(), _Normal))
		return false;

	return true;
}

Vector3 Render::Geometric_centroid_VertexCalc(const Vector3& _p1, const Vector3& _p2, 
														const Vector3& _p3,	const Vector3& _W)
{
	Vector3 u = _p1-_p3, v = _p2 - _p3, W = _W;	
	float udotv = MathLib::DotProduct(u.X, u.Y, v.X, v.Y),
		  wdotv = MathLib::DotProduct(_W.X, _W.Y, v.X, v.Y),
		  wdotu = MathLib::DotProduct(_W.X, _W.Y, u.X, u.Y),
		  uu = MathLib::DotProduct(u.X, u.Y, u.X, u.Y),
		  vv = MathLib::DotProduct(v.X, v.Y, v.X, v.Y);
	float invVal = udotv * udotv - uu * vv;

	if (invVal == 0) 
		invVal = 0.000000001;

	float s = (wdotv * udotv - wdotu * vv) / invVal;
	float t = (wdotu * udotv - wdotv * uu) / invVal;
	return std::move(Vector3(s, t, 1 - s - t));
}

void Render::SwithRenderType(const Vector3& _ObjPos, const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const PhongData& _PD)
{
	switch (Render_Type)
	{
		case RenderType::WireFrame:
		{
			if (Thread_Render)
			{
				ThreadPool_Component->EnqueueJob([this](Vertex tmp1, Vertex tmp2, Vertex tmp3)
					{ RasterizePolygon_wire(tmp1, tmp2, tmp3); }, _p1, _p2, _p3);
			}//멀티스레드 렌더링
			else
				RasterizePolygon_wire(_p1, _p2, _p3);
			//싱글스레드 렌더링
			break;
		}
		case RenderType::FlatShading:
		{
			if (Thread_Render)
			{
				ThreadPool_Component->EnqueueJob([this](Vertex tmp1, Vertex tmp2, Vertex tmp3)
					{ RasterizePolygon_Flat(tmp1, tmp2, tmp3, Color32(255, 100, 0)); }, _p1, _p2, _p3);
			}//멀티스레드 렌더링
			else
				RasterizePolygon_Flat(_p1, _p2, _p3, Color32(255, 100, 0));
			//싱글스레드 렌더링
			break;
		}
		case RenderType::PhongShading:
		{
			if (Thread_Render)
			{
				ThreadPool_Component->EnqueueJob([this](Vector3 _Position, Vertex tmp1, Vertex tmp2, Vertex tmp3, PhongData _PhongD)
					{ RasterizePolygon_Phong(_Position, tmp1, tmp2, tmp3, _PhongD); }, _ObjPos, _p1, _p2, _p3, _PD);
			}//멀티스레드 렌더링
			else
				RasterizePolygon_Phong(_ObjPos, _p1, _p2, _p3, _PD);
			//싱글스레드 렌더링
			break;
		}
		case RenderType::LightRender:
		{
			if (Thread_Render)
			{
				ThreadPool_Component->EnqueueJob([this](Vertex tmp1, Vertex tmp2, Vertex tmp3)
					{ RasterizePolygon_Light(tmp1, tmp2, tmp3, Color32(255, 100, 0)); }, _p1, _p2, _p3);
			}//멀티스레드 렌더링
			else
				RasterizePolygon_Light(_p1, _p2, _p3, Color32(255, 100, 0));
			//싱글스레드 렌더링
			break;
		}
		default:
		{
			if (Thread_Render)
			{
				ThreadPool_Component->EnqueueJob([this](Vertex tmp1, Vertex tmp2, Vertex tmp3)
					{ RasterizePolygon_Test(tmp1, tmp2, tmp3); }, _p1, _p2, _p3);
			}//멀티스레드 렌더링
			else
				RasterizePolygon_Test(_p1, _p2, _p3);
			//싱글스레드 렌더링
			break;
		}
	}
}

void Render::RasterizePolygon_Phong(const Vector3& _ObjPos, const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const PhongData& _PD)
{	
	if (!BackFaceCuling(_p1.NormalVec + _p2.NormalVec + _p3.NormalVec))
		return;
	//백페이스 컬링
	
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
		p.ClipTriangles(tmpVertices); //삼각형 클리핑(동차좌표계에서 진행 후 ndc 변환)
	
	if (tmpVertices.size() != 3)
		return;
	//절두체컬링
	MakePolygonViewPortData(tmpVertices);
	//ndc -> 뷰포트 진행

	Vector3 Vertices[3]{ Vector3(tmpVertices[0].Pos.X, tmpVertices[0].Pos.Y, tmpVertices[0].Pos.Z),
						Vector3(tmpVertices[1].Pos.X, tmpVertices[1].Pos.Y, tmpVertices[1].Pos.Z),
						Vector3(tmpVertices[2].Pos.X, tmpVertices[2].Pos.Y, tmpVertices[2].Pos.Z)};

	MathLib::SortByYvalue(Vertices, Vertices);
	for (int i = 0; i < 3; i++)
		Vertices[i] = MathLib::EraseDecimalXY(Vertices[i]);

	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);
	
	for (int i = Vertices[0].Y; i <= Vertices[2].Y; i++)
	{
		float StartX, EndX;
		if (i <= Vertices[1].Y)//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 작을 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i),
			EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);
		}
		else
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
			EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);
		}

		if (StartX > EndX)
			MathLib::SwapElement(&StartX, &EndX);
		//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
		//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
		//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)			

		for (int j = StartX; j <= EndX; j++)
		{					
			if(!DibSec.CheckIntersectClientRect(j, i))
				continue;
		
			Vector3 GeoPos = Geometric_centroid_VertexCalc(Vertices[0], Vertices[1], Vertices[2], 
																	Vector3(j, i, 0) - Vertices[2]);
			//무게중심 좌표계 생성
			if(GeoPos.X < 0.f || GeoPos.X > 1.f || GeoPos.Y < 0.f || GeoPos.Y > 1.f || GeoPos.Z < 0.f || GeoPos.Z > 1.f)
				continue;

			float invZ0 = 1.f / tmpVertices[0].Pos.W;
			float invZ1 = 1.f / tmpVertices[1].Pos.W;
			float invZ2 = 1.f / tmpVertices[2].Pos.W;
			float Z = invZ0 * GeoPos.Z + invZ1 * GeoPos.X + invZ2 * GeoPos.Y, invZ = 1.f / Z;
			float PixelZvalue = (Vertices[0].Z * GeoPos.X * invZ1 + Vertices[1].Z * GeoPos.Y * invZ2 + 
								Vertices[2].Z * GeoPos.Z * invZ0)*invZ;		
			//무게중심 좌표계 보간값
			EnterCriticalSection(&CRSC);
			if (!DepthBuf.CheckDepthBuffer(j, i, PixelZvalue))
			{
				LeaveCriticalSection(&CRSC);
				continue;
			}
			LeaveCriticalSection(&CRSC);
			//깊이버퍼 체크			
			Vector3 PixelNormal = ((tmpVertices[0].NormalVec * GeoPos.X * invZ1)
				+ (tmpVertices[1].NormalVec * GeoPos.Y * invZ2) + (tmpVertices[2].NormalVec * GeoPos.Z * invZ0))*invZ;			
			//무게중심 좌표계로 보간된 노말을 이용해 퐁 역산
			DibSec.DotPixel(j, i, MakePhongShader(_ObjPos, PixelNormal, _PD));			
		}				
	}
}

void Render::RasterizePolygon_wire(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3)
{
	if (!BackFaceCuling(_p1.NormalVec + _p2.NormalVec + _p3.NormalVec))
		return;
	//백페이스 컬링

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
		p.ClipTriangles(tmpVertices); //삼각형 클리핑(동차좌표계에서 진행 후 ndc 변환)

	if (tmpVertices.size() == 0)
		return;
	//절두체컬링
	MakePolygonViewPortData(tmpVertices);
	//ndc -> 뷰포트 진행

	Vector3 Vertices[3]{ Vector3(tmpVertices[0].Pos.X, tmpVertices[0].Pos.Y, tmpVertices[0].Pos.Z),
						Vector3(tmpVertices[1].Pos.X, tmpVertices[1].Pos.Y, tmpVertices[1].Pos.Z),
						Vector3(tmpVertices[2].Pos.X, tmpVertices[2].Pos.Y, tmpVertices[2].Pos.Z) };

	MathLib::SortByYvalue(Vertices, Vertices);
	for (int i = 0; i < 3; i++)

	Vertices[i] = MathLib::EraseDecimalXY(Vertices[i]);
	LineDraw(Vertices[0].X, Vertices[0].Y, Vertices[1].X, Vertices[1].Y, Color32(0, 0, 0));
	LineDraw(Vertices[0].X, Vertices[0].Y, Vertices[2].X, Vertices[2].Y, Color32(0, 0, 0));
	LineDraw(Vertices[2].X, Vertices[2].Y, Vertices[1].X, Vertices[1].Y, Color32(0, 0, 0));
}

void Render::RasterizePolygon_Flat(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const Color32& _Color)
{
	if (!BackFaceCuling(_p1.NormalVec + _p2.NormalVec + _p3.NormalVec))
		return;
	//백페이스 컬링

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
		p.ClipTriangles(tmpVertices); //삼각형 클리핑(동차좌표계에서 진행 후 ndc 변환)

	if (tmpVertices.size() == 0)
		return;
	//절두체컬링
	MakePolygonViewPortData(tmpVertices);
	//ndc -> 뷰포트 진행

	Vector3 Vertices[3]{ Vector3(tmpVertices[0].Pos.X, tmpVertices[0].Pos.Y, tmpVertices[0].Pos.Z),
						Vector3(tmpVertices[1].Pos.X, tmpVertices[1].Pos.Y, tmpVertices[1].Pos.Z),
						Vector3(tmpVertices[2].Pos.X, tmpVertices[2].Pos.Y, tmpVertices[2].Pos.Z) };

	MathLib::SortByYvalue(Vertices, Vertices);
	for (int i = 0; i < 3; i++)
		Vertices[i] = MathLib::EraseDecimalXY(Vertices[i]);

	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);

	for (int i = Vertices[0].Y; i <= Vertices[2].Y; i++)
	{
		float StartX, EndX;
		if (i <= Vertices[1].Y)//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 작을 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i),
				EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);
		}
		else
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
				EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);
		}

		if (StartX > EndX)
			MathLib::SwapElement(&StartX, &EndX);
		//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
		//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
		//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)			

		for (int j = StartX; j <= EndX; j++)
		{
			if (!DibSec.CheckIntersectClientRect(j, i))
				continue;

			Vector3 GeoPos = Geometric_centroid_VertexCalc(Vertices[0], Vertices[1], Vertices[2],
				Vector3(j, i, 0) - Vertices[2]);
			//무게중심 좌표계 생성
			if (GeoPos.X < 0.f || GeoPos.X > 1.f || GeoPos.Y < 0.f || GeoPos.Y > 1.f || GeoPos.Z < 0.f || GeoPos.Z > 1.f)
				continue;

			float invZ0 = 1.f / tmpVertices[0].Pos.W;
			float invZ1 = 1.f / tmpVertices[1].Pos.W;
			float invZ2 = 1.f / tmpVertices[2].Pos.W;
			float Z = invZ0 * GeoPos.Z + invZ1 * GeoPos.X + invZ2 * GeoPos.Y, invZ = 1.f / Z;
			float PixelZvalue = (Vertices[0].Z * GeoPos.X * invZ1 + Vertices[1].Z * GeoPos.Y * invZ2 +
				Vertices[2].Z * GeoPos.Z * invZ0) * invZ;
			//무게중심 좌표계 보간값
			EnterCriticalSection(&CRSC);
			if (!DepthBuf.CheckDepthBuffer(j, i, PixelZvalue))
			{
				LeaveCriticalSection(&CRSC);
				continue;
			}
			LeaveCriticalSection(&CRSC);
			//깊이버퍼 체크				
			DibSec.DotPixel(j, i, _Color);
		}
	}
}

void Render::RasterizePolygon_Test(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3)
{
	//if (!BackFaceCuling(_p1.NormalVec + _p2.NormalVec + _p3.NormalVec))
	//	return;
	//백페이스 컬링

	std::vector<Vertex> tmpVertices{ _p1, _p2, _p3 };
                    
	Vector3 Vertices[3]{ Vector3(tmpVertices[0].Pos.X, tmpVertices[0].Pos.Y, tmpVertices[0].Pos.Z),
						Vector3(tmpVertices[1].Pos.X, tmpVertices[1].Pos.Y, tmpVertices[1].Pos.Z),
						Vector3(tmpVertices[2].Pos.X, tmpVertices[2].Pos.Y, tmpVertices[2].Pos.Z) };

	MathLib::SortByYvalue(Vertices, Vertices);
	for (int i = 0; i < 3; i++)
		Vertices[i] = MathLib::EraseDecimalXY(Vertices[i]);

	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);

	for (int i = Vertices[0].Y; i <= Vertices[2].Y; i++)
	{
		float StartX, EndX;
		if (i <= Vertices[1].Y)//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 작을 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i),
				EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);
		}
		else
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
				EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);
		}

		if (StartX > EndX)
			MathLib::SwapElement(&StartX, &EndX);
		//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
		//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
		//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)			

		for (int j = StartX; j <= EndX; j++)
		{
			if (!DibSec.CheckIntersectClientRect(j + ClientX, i + ClientY))
				continue;		
	
			DibSec.DotPixel(j + ClientX, i + ClientY, Color32(255,100,100));
		}
	}
}

void Render::RasterizePolygon_Light(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const Color32& _Color)
{
	//if (!BackFaceCuling(_p1.NormalVec + _p2.NormalVec + _p3.NormalVec))
	//	return;
	//백페이스 컬링

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
		p.ClipTriangles(tmpVertices); //삼각형 클리핑(동차좌표계에서 진행 후 ndc 변환)

	if (tmpVertices.size() == 0)
		return;
	//절두체컬링
	MakePolygonViewPortData(tmpVertices);
	//ndc -> 뷰포트 진행

	Vector3 Vertices[3]{ Vector3(tmpVertices[0].Pos.X, tmpVertices[0].Pos.Y, tmpVertices[0].Pos.Z),
						Vector3(tmpVertices[1].Pos.X, tmpVertices[1].Pos.Y, tmpVertices[1].Pos.Z),
						Vector3(tmpVertices[2].Pos.X, tmpVertices[2].Pos.Y, tmpVertices[2].Pos.Z) };

	MathLib::SortByYvalue(Vertices, Vertices);
	for (int i = 0; i < 3; i++)
		Vertices[i] = MathLib::EraseDecimalXY(Vertices[i]);

	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);	

	for (int i = Vertices[0].Y; i <= Vertices[2].Y; i++)
	{
		float StartX, EndX;
		if (i <= Vertices[1].Y)//Y값의 크기로 정렬 된 버텍스리스트의 중간값보다 작을 때(X,y 기울기 0은 절편을 구하기때문에 고려x)
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i),
				EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);
		}
		else
		{
			StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
				EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);
		}

		if (StartX > EndX)
			MathLib::SwapElement(&StartX, &EndX);
		//버텍스 3개의 값을 y값 오름차순으로 정렬하여 각 정점끼리의 직선의 방정식을 생성,
		//최소y에서 최대y까지의 길이사이에서 각 직선의 방정식을 이용하여 i = y 지점의 양 직선 사이의 점을 구하고
		//두 점 사이의 모든 빈자리를 채움(삼각형 내부에 직선을 그리는 식으로 삼각형을 모두 채움)			

		for (int j = StartX; j <= EndX; j++)
		{
			if (!DibSec.CheckIntersectClientRect(j, i))
				continue;

			Vector3 GeoPos = Geometric_centroid_VertexCalc(Vertices[0], Vertices[1], Vertices[2],
				Vector3(j, i, 0) - Vertices[2]);
			//무게중심 좌표계 생성
			if (GeoPos.X < 0.f || GeoPos.X > 1.f || GeoPos.Y < 0.f || GeoPos.Y > 1.f || GeoPos.Z < 0.f || GeoPos.Z > 1.f)
				continue;

			float invZ0 = 1.f / tmpVertices[0].Pos.W;
			float invZ1 = 1.f / tmpVertices[1].Pos.W;
			float invZ2 = 1.f / tmpVertices[2].Pos.W;
			float Z = invZ0 * GeoPos.Z + invZ1 * GeoPos.X + invZ2 * GeoPos.Y, invZ = 1.f / Z;
			float PixelZvalue = (Vertices[0].Z * GeoPos.X * invZ1 + Vertices[1].Z * GeoPos.Y * invZ2 +
				Vertices[2].Z * GeoPos.Z * invZ0) * invZ;
			//무게중심 좌표계 보간값
			EnterCriticalSection(&CRSC);
			if (!DepthBuf.CheckDepthBuffer(j, i, PixelZvalue))
			{
				LeaveCriticalSection(&CRSC);
				continue;
			}
			LeaveCriticalSection(&CRSC);
			//깊이버퍼 체크				
			DibSec.DotPixel(j, i, _Color);
		}
	}
}

Color32 Render::MakePhongShader(const Vector3& _ObjPos, const Vector3& _PixelNormal, const PhongData& _PD)
{
	//방향광을 전제로 계산(픽셀에서 광원과의 노말을 구하는데는 연산량이 너무 늘어나서 방향광으로 선택)
	auto Lighting = ObjectMng_Component->GetLightSun();
	Vector3 l_DirLight = (_ObjPos - Lighting->GetPosition()).GetNormalVector();
	float ldotPixNor = MathLib::DotProduct((l_DirLight), _PixelNormal);
	Vector3	v_ObjToCamera = (_ObjPos - Camera_Component->GetPosition()).GetNormalVector();	
	float a_Shining = LightObj::ShiningConst;	
	Vector3	Ambient, Diffuse, Specular;

	if (ldotPixNor >= 0)
	{
		Ambient = Lighting->GetKAmb() * _PD.Ambient,
		Diffuse = Lighting->GetKDiff() * _PD.Diffuse * max(-1 * MathLib::DotProduct(_PixelNormal, l_DirLight), 0.f);
		Specular.X = 0; Specular.Y = 0; Specular.Z = 0;
	}
	else
	{
		Vector3	r_ReflectVec = (-2 * ldotPixNor * _PixelNormal + l_DirLight).GetNormalVector();
		Ambient = Lighting->GetKAmb() * _PD.Ambient,
		Diffuse = Lighting->GetKDiff() * _PD.Diffuse * max(-1 * MathLib::DotProduct(_PixelNormal, l_DirLight), 0.f);
		Specular = Lighting->GetKSpec() * _PD.Specular * pow(max(-1 * MathLib::DotProduct(r_ReflectVec, v_ObjToCamera), 0.f), a_Shining);
	}	
	
	return Color32(Ambient.X + Diffuse.X + Specular.X, Ambient.Y + Diffuse.Y + Specular.Y, Ambient.Z + Diffuse.Z + Specular.Z);
}

void Render::LineDraw(int _x1, int _y1, int _x2, int _y2, const Color32& _color)
{
	bool yLonger = false;
	int shortLen = _y2 - _y1;
	int longLen = _x2 - _x1;


	if (abs(shortLen) > abs(longLen))
	{
		int swap = shortLen;
		shortLen = longLen;
		longLen = swap;
		yLonger = true;
	}

	int decInc;

	if (longLen == 0)
		decInc = 0;
	else
		decInc = (shortLen << 16) / longLen;

	if (yLonger)
	{
		if (longLen > 0)
		{
			longLen += _y1;

			for (int j = 0x8000 + (_x1 << 16); _y1 <= longLen; ++_y1)
			{
				if (!DibSec.CheckIntersectClientRect(j >> 16, _y1))
					continue;

				DibSec.DotPixel(j >> 16, _y1, _color);
				j += decInc;
			}
			return;
		}

		longLen += _y1;

		for (int j = 0x8000 + (_x1 << 16); _y1 >= longLen; --_y1)
		{
			if (!DibSec.CheckIntersectClientRect(j >> 16, _y1))
				continue;

			DibSec.DotPixel(j >> 16, _y1, _color);
			j -= decInc;
		}
		return;
	}

	if (longLen > 0)
	{
		longLen += _x1;
		for (int j = 0x8000 + (_y1 << 16); _x1 <= longLen; ++_x1)
		{
			if (!DibSec.CheckIntersectClientRect(_x1, j >> 16))
				continue;

			DibSec.DotPixel(_x1, j >> 16, _color);
			j += decInc;
		}
		return;
	}

	longLen += _x1;

	for (int j = 0x8000 + (_y1 << 16); _x1 >= longLen; --_x1)
	{
		if (!DibSec.CheckIntersectClientRect(_x1, j >> 16))
			continue;

		DibSec.DotPixel(_x1, j >> 16, _color);
		j -= decInc;
	}

	return;
}

void Render::RenderFPS(float _elapsedTime)
{
	DibSec.SetWindowsTitleFPS(_elapsedTime);
}

