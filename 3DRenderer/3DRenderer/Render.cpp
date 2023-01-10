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
}

void Render::OnRender(float _elapsedTime)
{
	if (ThreadPool_Component == nullptr || ObjectMng_Component == nullptr || Camera_Component == nullptr)
		return;

	PrepareObj_for_Render();
	RenderObj();
	BitBltDib();
	//DibSec.BitBltDibSection(); //�̱۽����� �������� ����
	DepthBuf.ClearDepthBuffer();
}

void Render::PrepareObj_for_Render()
{
	Camera_Component->MakeViewMatrix();
	ObjectMng_Component->PrepareRender_MakeMat(Camera_Component->GetCameraMat(), Projection->GetProjMat());
}

void Render::MakePolygonNDCData(Vertex* _vt, const Matrix44& _FinalMat, const Matrix44& _WrdViewMat)
{
	for (int i = 0; i < 3; i++)
	{
		_vt[i].MakeRenderdata(_FinalMat, _WrdViewMat);
		_vt[i].Pos.X = _vt[i].Pos.X / _vt[i].Pos.W;
		_vt[i].Pos.Y = _vt[i].Pos.Y / _vt[i].Pos.W;
		_vt[i].Pos.Z = _vt[i].Pos.Z / _vt[i].Pos.W;

		_vt[i].Pos.X = _vt[i].Pos.X * ClientX + ClientX;
		_vt[i].Pos.Y = -_vt[i].Pos.Y * ClientY + ClientY;	
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
		Matrix44 WrdViewMat = ObjectMng_Component->GetObj_WrdViewMat(i);

		for (auto& j : *Indicies)
		{		
			Vertex tmp[3]{ (*Vertices)[j._0] , (*Vertices)[j._1] , (*Vertices)[j._2] }; 	
			MakePolygonNDCData(tmp, FMat, WrdViewMat);
			ThreadPool_Component->EnqueueJob([this](Vector3 _Position, Vertex tmp1, Vertex tmp2, 
																		Vertex tmp3, PhongData _PhongD) 
			{ RasterizePolygon(_Position, tmp1, tmp2, tmp3, _PhongD); }, Position, tmp[0], tmp[1], tmp[2], PhoD);

			//RasterizePolygon(Position,	tmp[0], tmp[1], tmp[2], PhoD); //�̱۽����� ������
		}
	}
}

bool Render::BackSpaceCuling(const Vector3& _Normal)
{
	if (0 > MathLib::DotProduct(Camera_Component->GetNormal(), _Normal))
		return false;

	return true;
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

void Render::RasterizePolygon(const Vector3& _ObjPos, const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const PhongData& _PD)
{	
	if (!BackSpaceCuling(_p1.NormalVec + _p2.NormalVec + _p3.NormalVec))
		return;
	
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
		p.ClipTriangles(tmpVertices); //�ﰢ�� Ŭ����(ndc �������� �ﰢ�� ��������)
	
	if (tmpVertices.size() == 0)
		return;
	
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
		if (i <= Vertices[1].Y)//Y���� ũ��� ���� �� ���ؽ�����Ʈ�� �߰������� ���� ��(X,y ���� 0�� ������ ���ϱ⶧���� ���x)
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
		//���ؽ� 3���� ���� y�� ������������ �����Ͽ� �� ���������� ������ �������� ����,
		//�ּ�y���� �ִ�y������ ���̻��̿��� �� ������ �������� �̿��Ͽ� i = y ������ �� ���� ������ ���� ���ϰ�
		//�� �� ������ ��� ���ڸ��� ä��(�ﰢ�� ���ο� ������ �׸��� ������ �ﰢ���� ��� ä��)			

		for (int j = StartX; j < EndX; j++)
		{					
			//PhongShader(������ �븻���� ���� ����Ʈ �ݻ簪 �����ġ)
			if(!DibSec.CheckIntersectClientRect(j, i))
				continue;
			/*
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
			//���̹��� üũ			
			Vector3 PixelNormal = (tmpVertices[0].NormalVec * GeoPos.X)
				+ (tmpVertices[1].NormalVec * GeoPos.Y) + (tmpVertices[2].NormalVec * GeoPos.Z);				
			DibSec.DotPixel(ResultX, ResultY, MakePhongShader(_ObjPos, PixelNormal, _PD));				
			*/
			DibSec.DotPixel(j, i, Color32(255, 0, 0, 255));//test			
		}				
	}
}

Color32 Render::MakePhongShader(const Vector3& _ObjPos, const Vector3& _PixelNormal, const PhongData& _PD)
{
	//���Ɽ�� ������ ���(�ȼ����� �������� �븻�� ���ϴµ��� ���귮�� �ʹ� �þ�� ���Ɽ���� ����)
	LightObj* Lighting = ObjectMng_Component->GetLightSun();
	Vector3 l_DirLight = _ObjPos - Lighting->GetPosition();
	Vector3 v_ObjToCamera = _ObjPos - Camera_Component->GetPosition();
	Vector3 r_ReflectVec = -2 * (MathLib::DotProduct((-1 * l_DirLight), _PixelNormal)) * _PixelNormal - l_DirLight;
	float a_Shining = LightObj::ShiningConst;

	Vector3 Ambient = Lighting->GetKAmb() * _PD.Ambient,
			Diffuse = Lighting->GetKDiff() * _PD.Diffuse * (MathLib::DotProduct(_PixelNormal, l_DirLight)),
			Specular = Lighting->GetKSpec() *_PD.Specular * pow(MathLib::DotProduct(r_ReflectVec, v_ObjToCamera), a_Shining);

	return Color32(Ambient.X + Diffuse.X + Specular.X, Ambient.Y + Diffuse.Y + Specular.Y, 
														Ambient.Z + Diffuse.Z + Specular.Z);
}

void Render::RenderFPS(float _elapsedTime)
{
	DibSec.SetWindowsTitleFPS(_elapsedTime);
}

